/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:38:38 by rlane             #+#    #+#             */
/*   Updated: 2024/11/07 13:31:26 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number_str(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cmd_exit(t_node *node)
{
	int		exit_status;
	char	*s;

	exit_status = 0;
	s = node->args[1];
	if (s)
	{
		if (node->args[2])
		{
			ft_putstr_fd(" too many arguments\n", 2);
			exit(1);
		}
		if (!is_number_str(s))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			exit(2);
		}
		exit_status = ft_atoi(s) % 256;
	}
	exit(exit_status);
}

static void	trim_args(t_node *node)
{
	int	i;

	if (!node->args[1])
		printf("\n");
	else if (node->args[1])
	{
		i = 0;
		while (node->args[i + 1])
		{
			free(node->args[i]);
			node->args[i] = ft_strdup(node->args[i + 1]);
			i++;
		}
		free(node->args[i]);
		node->args[i] = NULL;
		exec_cmd(node);
	}
}

void	exec_cmd(t_node *node)
{
	if (node->args[0] == NULL)
		return ;
	else if (!my_strcmp(node->args[0], "help"))
		cmd_help();
	else if (!my_strcmp(node->args[0], "pwd"))
		cmd_pwd(node);
	else if (!my_strcmp(node->args[0], "cd"))
		cmd_cd(node);
	else if (!my_strcmp(node->args[0], "echo"))
		cmd_echo(node);
	else if (!my_strcmp(node->args[0], "env"))
		cmd_env(node);
	else if (!my_strcmp(node->args[0], "unset"))
		cmd_unset(node);
	else if (!my_strcmp(node->args[0], "export"))
		cmd_export(node);
	else if (!my_strcmp(node->args[0], ""))
		trim_args(node);
	else if (!my_strcmp(node->args[0], "exit"))
		cmd_exit(node);
	else
		call_external_cmd(node, NULL);
}
