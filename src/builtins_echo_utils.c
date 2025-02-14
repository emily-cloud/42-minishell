/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:35:47 by rlane             #+#    #+#             */
/*   Updated: 2024/11/11 16:27:51 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_home(t_env_node *env, const char *name)
{
	t_env_node	*temp;
	char		*home_path;

	temp = env;
	home_path = NULL;
	while (temp)
	{
		if (!my_strcmp(temp->name, name))
		{
			home_path = ft_strdup(temp->value);
			if (home_path == NULL)
			{
				perror("Memory allocation failed");
			}
			break ;
		}
		temp = temp->next;
	}
	return (home_path);
}

void	expand_tilda(t_node *node)
{
	int		i;
	char	*new_value;

	i = 1;
	while (node->args[i])
	{
		if (node->args[i][0] == '~' && !node->args[i][1])
		{
			new_value = update_home(node->shell->env, "HOME");
			if (new_value)
			{
				free(node->args[i]);
				node->args[i] = new_value;
			}
		}
		i++;
	}
}
