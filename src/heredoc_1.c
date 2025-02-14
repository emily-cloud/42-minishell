/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:42:48 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 13:20:31 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_right_wait_exit(t_node *node, int pipe_fd[2], int pid_right,
	int *status)
{
	while (waitpid(pid_right, status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		else
		{
			perror("waitpid");
			close(pipe_fd[0]);
			set_last_exit_status(node, 1);
			return (1);
		}
	}
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		set_last_exit_status(node, 130);
		return (1);
	}
	else if (WIFEXITED(*status) && WEXITSTATUS(*status) != 0)
	{
		set_last_exit_status(node, WEXITSTATUS(*status));
		return (1);
	}
	return (0);
}

// Child process handling heredoc input
// Reset signal handlers to default

int	heredoc_right_child(t_node *node, int pipe_fd[2], int *status)
{
	int	pid_right;

	pid_right = fork_and_check_pid();
	if (pid_right == 0)
	{
		close(pipe_fd[0]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		recurse_heredocs(node, pipe_fd);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[1]);
	if (heredoc_right_wait_exit(node, pipe_fd, pid_right, status))
		return (1);
	return (0);
}

int	heredoc_fork_left(t_node *node, int pipe_fd[2], int *status)
{
	int			pid_left;
	t_node		*temp;

	temp = node;
	pid_left = fork_and_check_pid();
	if (pid_left == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		while (temp->left && temp->left->type == OP_HEREDOC)
			temp = temp->left;
		dup2(node->active_fd_out, STDOUT_FILENO);
		if (temp->left)
			exec_tree(temp->left);
		set_last_exit_status_exit_success(node, 0);
	}
	close(pipe_fd[0]);
	if (waitpid(pid_left, status, 0) == -1)
	{
		perror("waitpid");
		set_last_exit_status(node, 1);
		return (1);
	}
	return (0);
}

int	heredoc_left_child(t_node *node, int pipe_fd[2], int *status)
{
	if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
	{
		if (heredoc_fork_left(node, pipe_fd, status))
			return (1);
	}
	else if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		reset_stin_stout(node);
		printf("Heredoc process interrupted\n");
		close(pipe_fd[0]);
		set_last_exit_status(node, 130);
		return (1);
	}
	else
	{
		write(2, "Heredoc process failed\n", 24);
		close(pipe_fd[0]);
		set_last_exit_status(node, 1);
		return (1);
	}
	return (0);
}

void	exec_heredoc(t_node *node)
{
	int		pipe_fd[2];
	int		status;

	status = 0;
	if (!node->right)
		return ;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		set_last_exit_status(node, 1);
		return ;
	}
	if (heredoc_right_child(node, pipe_fd, &status))
		return ;
	if (heredoc_left_child(node, pipe_fd, &status))
		return ;
	dup2(node->shell->original_stdin, STDIN_FILENO);
	dup2(node->shell->original_stdout, STDOUT_FILENO);
}
