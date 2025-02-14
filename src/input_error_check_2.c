/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_check_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:10:22 by hai               #+#    #+#             */
/*   Updated: 2024/11/12 14:03:24 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error_message(t_node *top, char *message)
{
	ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	if (top)
		set_last_exit_status(top, 2);
}

int	is_type_op(t_node_type type)
{
	if (type == OP_REDIR_IN || type == OP_REDIR_OUT || type == OP_REDIR_APPEND
		|| type == OP_PIPE || type == OP_AND || type == OP_OR)
		return (1);
	return (0);
}

int	check_top(t_node *top)
{
	if (!top || top->type == OP_PIPE || top->type == OP_AND
		|| top->type == OP_OR)
	{
		if (!top)
			write_error_message(top, "newline");
		else
			write_error_message(top, top->args[0]);
		return (1);
	}
	if ((top->type == OP_REDIR_IN || top->type == OP_REDIR_OUT
			|| top->type == OP_REDIR_APPEND)
		&& (!top->right || is_type_op(top->right->type)))
	{
		write_error_message(top, "newline");
		return (1);
	}
	if (top->right && top->right->type == ARG_FILE
		&& is_op(top->right->content))
	{
		write_error_message(top, top->args[0]);
		return (1);
	}
	return (0);
}

int	check_pipe_and_or(t_node *top)
{
	if (top->type == OP_PIPE || top->type == OP_AND || top->type == OP_OR)
	{
		if (top->right == NULL)
		{
			write_error_message(top, top->args[0]);
			return (1);
		}
		if (top->right && (top->right->type == OP_PIPE
				|| top->right->type == OP_AND || top->right->type == OP_OR))
		{
			write_error_message(top, top->args[0]);
			return (1);
		}
	}
	return (0);
}

int	check_cmd(t_node *top)
{
	if (top->type == CMD)
	{
		if (top->right && top->right->type == CMD)
		{
			write_error_message(top, top->args[0]);
			return (1);
		}
		else if (top->right && top->right->content[0] == '(')
		{
			write_error_message(top, top->args[0]);
			return (1);
		}
	}
	return (0);
}
