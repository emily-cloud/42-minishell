/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:46:26 by rlane             #+#    #+#             */
/*   Updated: 2024/11/10 12:37:10 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_brackets(t_node *node)
{
	int		len;
	char	*content;

	len = ft_strlen(node->args[0]);
	if (node->args[0][0] == '(' && node->args[0][len - 1] == ')')
	{
		content = ft_substr(node->args[0], 1, len - 2);
		free(node->args[0]);
		node->args[0] = content;
	}
}

void	exec_sub_shell(t_node *node)
{
	int		status;
	pid_t	pid;

	trim_brackets(node);
	if (node->args[0] == NULL || *node->args[0] == '\0')
		return ;
	pid = fork();
	if (pid == 0)
	{
		parse_line(node->args[0], node->shell);
		exit(node->shell->last_exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		set_last_exit_status(node, WEXITSTATUS(status));
	}
}
