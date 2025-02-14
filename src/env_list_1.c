/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:42:29 by hai               #+#    #+#             */
/*   Updated: 2024/10/15 18:43:19 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*create_node(char **str, int export_status)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->name = ft_strdup(str[0]);
	if (str[1])
		new_node->value = ft_strdup(str[1]);
	new_node->next = NULL;
	new_node->exported = export_status;
	return (new_node);
}

void	add_env_node(char **str, t_env_node *head, int export_status)
{
	t_env_node	*temp;

	temp = head;
	if (head == NULL)
	{
		head = create_node(str, export_status);
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = create_node(str, export_status);
}

char	*get_env_name(char *env, char *equal_sign)
{
	if (equal_sign)
		return (ft_substr(env, 0, equal_sign - env));
	return (ft_strdup(env));
}

char	*get_env_value(char *equal_sign)
{
	if (equal_sign)
		return (ft_strdup(equal_sign + 1));
	return (ft_strdup(""));
}

void	set_env_list(t_shell *shell, char **envp, int export_status)
{
	char	*name;
	char	*value;
	char	*equal_sign;
	int		i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		name = get_env_name(envp[i], equal_sign);
		value = get_env_value(equal_sign);
		if (i == 0)
			shell->env = create_node((char *[]){name, value}, export_status);
		else
			add_env_node((char *[]){name, value}, shell->env, export_status);
		free(name);
		free(value);
		i++;
	}
	add_env_node((char *[]){"?", "0"}, shell->env, NOT_EXPORTED);
}
