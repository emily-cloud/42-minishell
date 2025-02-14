/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_check_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:10:22 by hai               #+#    #+#             */
/*   Updated: 2024/11/10 12:52:07 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_path_search(t_node *node)
{
	struct stat		path_stat;

	if (stat(node->args[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			set_last_exit_status(node, 126);
			return (2);
		}
		else if (S_ISREG(path_stat.st_mode))
			return (0);
	}
	else
	{
		ft_putstr_fd(node->args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		set_last_exit_status(node, 127);
		return (2);
	}
	return (0);
}

static int	is_file_path(char *str)
{
	if ((ft_strncmp(str, "/", 1) == 0) || (ft_strncmp(str, "./", 2) == 0)
		|| (ft_strncmp(str + (ft_strlen(str) - 1), "/", 1) == 0))
		return (1);
	return (0);
}

static int	check_redirects(t_node *top)
{
	if (top->type == OP_REDIR_IN || top->type == OP_REDIR_OUT
		|| top->type == OP_REDIR_APPEND)
	{
		if (!top->right)
			return (write_error_message(top, "newline"), 1);
		if (top->right->args[0] == NULL || top->right->args[0][0] == '\0')
			return (write_error_message(top, "newline"), 2);
		if (top->right->type == ARG_FILE)
		{
			if (!my_strcmp(top->right->content, "*"))
			{
				ft_putstr_fd(" ambiguous redirect\n", STDERR_FILENO);
				set_last_exit_status(top, 1);
				return (1);
			}
			if (is_file_path(top->args[0]))
				return (file_path_search(top->right));
			return (0);
		}
		return (write_error_message(top, top->args[0]), 1);
	}
	return (0);
}

static int	check_heredoc(t_node *top)
{
	if (top->type == OP_HEREDOC)
	{
		if (!top->right)
		{
			write_error_message(top, "newline");
			return (1);
		}
		else if (top->right && top->right->type != DELIMITER)
		{
			write_error_message(top, top->args[0]);
			return (1);
		}
	}
	return (0);
}

int	input_error_check(t_node *top)
{
	if (check_top(top))
		return (1);
	while (top)
	{
		if (check_pipe_and_or(top))
			return (1);
		if (check_cmd(top))
			return (1);
		if (check_redirects(top))
			return (1);
		if (check_heredoc(top))
			return (1);
		top = top->right;
	}
	return (0);
}
