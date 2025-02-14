/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:24 by hai               #+#    #+#             */
/*   Updated: 2024/10/16 12:09:57 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_left_child_close_fd_exit(t_node *current, int fd)
{
	if (current->left && current->left->type != OP_REDIR_IN)
		exec_tree(current->left);
	else if (current->left && current->left->type == OP_REDIR_IN)
		exec_redir_in(current->left, 0);
	close(fd);
}

int	open_file_for_reading(t_node *current)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	file = ft_strdup(current->right->args[i]);
	while (current->right->args[++i])
	{
		free(file);
		file = ft_strdup(current->right->args[i]);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free(file);
		exit(EXIT_FAILURE);
	}
	free(file);
	return (fd);
}

void	handle_fd_duplication(int *fd_final, int *fd, t_node *current,
int *call_order)
{
	if (*call_order == 0)
		*fd_final = *fd;
	if (*fd_final)
		*fd = *fd_final;
	check_fd_an_dup2(*fd, STDIN_FILENO, current);
	(*call_order)++;
}

void	exec_redir_in(t_node *current, int reset)
{
	static int	fd_final;
	static int	call_order;
	pid_t		pid;
	int			fd;

	if (reset)
	{
		fd_final = -1;
		call_order = 0;
		return ;
	}
	pid = fork_and_check_pid();
	if (pid == 0)
	{
		fd = open_file_for_reading(current);
		handle_fd_duplication(&fd_final, &fd, current, &call_order);
		exec_left_child_close_fd_exit(current, fd);
		exit_child(current);
	}
	else
	{
		waitpid(pid, &current->shell->last_exit_status, 0);
		set_last_exit_status(current,
			WEXITSTATUS(current->shell->last_exit_status));
	}
}
