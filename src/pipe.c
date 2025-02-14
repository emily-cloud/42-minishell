/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:59:36 by hai               #+#    #+#             */
/*   Updated: 2024/11/11 12:59:45 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child(t_node *node)
{
	if (node->shell->last_exit_status != 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	pipe_left(t_node *node, int fd[2], pid_t *pid_left)
{
	*pid_left = fork_and_check_pid();
	if (*pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (node->left)
			exec_tree(node->left);
		exit_child(node);
	}
	close(fd[1]);
	if (node->right && my_strcmp(node->right->args[0], "exit") == 0)
	{
		waitpid(*pid_left, NULL, 0);
		close(fd[0]);
		dup2(node->shell->original_stdout, STDOUT_FILENO);
		free_shell(node->shell);
		exit(EXIT_SUCCESS);
	}
}

void	pipe_right(t_node *node, int fd[2], pid_t *pid_right)
{
	*pid_right = fork_and_check_pid();
	if (*pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (node->right)
			exec_tree(node->right);
		exit_child(node);
	}
	close(fd[0]);
}

static void	init_var(pid_t *pid_left, pid_t *pid_right,
	int *status_left, int *status_right)
{
	*pid_left = 0;
	*pid_right = 0;
	*status_left = 0;
	*status_right = 0;
}

void	exec_pipe(t_node *node)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	init_var(&pid_left, &pid_right, &status_left, &status_right);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	node->left->active_fd_out = fd[1];
	if (node->left && node->left->type == OP_HEREDOC)
		exec_heredoc(node->left);
	else
		pipe_left(node, fd, &pid_left);
	pipe_right(node, fd, &pid_right);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	reset_stin_stout(node);
	if (WEXITSTATUS(status_right))
		set_last_exit_status(node, 1);
	else
		set_last_exit_status(node, 0);
}
