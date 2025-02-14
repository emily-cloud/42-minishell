/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_append_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:22:54 by hai               #+#    #+#             */
/*   Updated: 2024/11/11 16:28:26 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_left_child_close_fd_exit(t_node *current, int fd)
{
	if (current->left && current->left->type != OP_REDIR_OUT
		&& current->left->type != OP_REDIR_APPEND)
		exec_tree(current->left);
	if (current->left && (current->left->type == OP_REDIR_OUT
			|| current->left->type == OP_REDIR_APPEND))
		exec_redir_out_append(current->left, 0);
	close(fd);
}

void	open_check(t_node *current, int *fd)
{
	if (current->type == OP_REDIR_OUT)
		*fd = open(current->right->args[0],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == OP_REDIR_APPEND)
		*fd = open(current->right->args[0],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		perror(current->right->args[0]);
		set_last_exit_status(current, 1);
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_node *current, pid_t pid)
{
	int	status;

	if (current->left && current->left->args[0]
		&& my_strcmp(current->left->args[0], "exit") == 0)
	{
		waitpid(pid, &current->shell->last_exit_status, 0);
		dup2(current->shell->original_stdout, STDOUT_FILENO);
		free_shell(current->shell);
		printf("exit\n");
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		set_last_exit_status(current, WEXITSTATUS(status));
	}
}

void	exec_redir_out_append(t_node *current, int reset)
{
	int			fd;
	pid_t		pid;
	static int	fd_final;
	static int	call_order;

	if (reset)
	{
		fd_final = -1;
		call_order = 0;
		return ;
	}
	pid = fork_and_check_pid();
	if (pid == 0)
	{
		open_check(current, &fd);
		if (call_order == 0)
			fd_final = fd;
		if (fd_final)
			fd = fd_final;
		check_fd_an_dup2(fd, STDOUT_FILENO, current);
		call_order++;
		exec_left_child_close_fd_exit(current, fd);
		exit_child(current);
	}
	parent_process(current, pid);
}
