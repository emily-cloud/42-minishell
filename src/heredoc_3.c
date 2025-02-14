/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:40:33 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 14:07:35 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signal(int *pipe_fd, char *line)
{
	if (g_sigint_received)
	{
		free(line);
		close(pipe_fd[1]);
		exit(130);
	}
}

void	check_signal_read_to_pipe(t_node *node, int pipe_fd[2])
{
	char	*line;

	while (!g_sigint_received)
	{
		dup2(node->shell->original_stdout, STDOUT_FILENO);
		line = readline(ORANGE "> " RESET);
		if (!line)
		{
			ft_putstr_fd(HEREDOC_ERROR, 2);
			write(2, node->right->args[0], ft_strlen(node->right->args[0]));
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (my_strcmp(line, node->right->args[0]) == 0)
		{
			free(line);
			break ;
		}
		line = expand_dollar_string(node, line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	check_signal(pipe_fd, line);
}

void	recurse_heredocs(t_node *node, int pipe_fd[2])
{
	int		temp_pipe[2];
	char	buffer[1024];

	if (node->left && node->left->type == OP_HEREDOC)
	{
		if (pipe(temp_pipe) == -1)
		{
			perror("pipe");
			return ;
		}
		recurse_heredocs(node->left, temp_pipe);
		close(temp_pipe[1]);
	}
	check_signal_read_to_pipe(node, pipe_fd);
	if (node->left && node->left->type == OP_HEREDOC)
	{
		while (read(temp_pipe[0], buffer, sizeof(buffer)) > 0)
			;
		close(temp_pipe[0]);
	}
}
