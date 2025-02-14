/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:42:29 by hai               #+#    #+#             */
/*   Updated: 2024/10/16 09:41:44 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*get_env_node(t_env_node *head, char *name)
{
	t_env_node	*current;

	current = head;
	while (current)
	{
		if (!my_strcmp(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	reset_or_add_env_var(t_node *node, char *key,
			char *new_value, int exported)
{
	t_env_node	*env_node;

	env_node = get_env_node(node->shell->env, key);
	if (env_node)
	{
		set_env_value(node->shell->env, key,
			new_value, EXPORTED);
	}
	else
	{
		add_env_node((char *[]){key, new_value}, node->shell->env, exported);
	}
}

static void	swap_nodes(t_env_node *a, t_env_node *b)
{
	char	*temp_name;
	char	*temp_value;
	int		temp_exported;

	temp_name = a->name;
	temp_value = a->value;
	temp_exported = a->exported;
	a->name = b->name;
	a->value = b->value;
	a->exported = b->exported;
	b->name = temp_name;
	b->value = temp_value;
	b->exported = temp_exported;
}

void	sort_list(t_env_node **head)
{
	t_env_node	*current;
	t_env_node	*next_node;
	int			swapped;

	if (!head || !(*head) || !((*head)->next))
		return ;
	swapped = 1;
	while (swapped)
	{
		current = *head;
		swapped = 0;
		while (current->next != NULL)
		{
			next_node = current->next;
			if (my_strcmp(current->name, next_node->name) > 0)
			{
				swap_nodes(current, next_node);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

int	count_env_nodes(t_env_node *env)
{
	t_env_node	*current;
	int			i;

	current = env;
	i = 0;
	while (current)
	{
		if (current->exported)
			i++;
		current = current->next;
	}
	return (i);
}
