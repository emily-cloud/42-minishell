/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:29:27 by hai               #+#    #+#             */
/*   Updated: 2024/10/17 14:07:40 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_env_node *env, char *name, char *value,
		int export_status)
{
	(void)export_status;
	while (env)
	{
		if (!my_strcmp(env->name, name))
		{
			free(env->value);
			if (value == NULL)
				return ;
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

void	print_variable(t_env_node *env, char *name)
{
	t_env_node	*temp;

	temp = env;
	while (temp)
	{
		if (!my_strcmp(temp->name, name))
		{
			ft_printf("%s\n", temp->value);
			break ;
		}
		temp = temp->next;
	}
}

void	cmd_cd(t_node *node)
{
	if (node->args[1] == NULL || node->args[1][0] == '\0')
		ch_home(node);
	else if (node->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		set_last_exit_status(node, 1);
		return ;
	}
	else if (!my_strcmp(node->args[1], "~"))
		ch_home(node);
	else if (!my_strcmp(node->args[1], "-"))
		ch_oldpwd(node);
	else if (node->args[1][0] == '~' && node->args[1][1])
		ch_home_sub(node->args[1], node);
	else
		ch_path(node->args[1], node);
}
