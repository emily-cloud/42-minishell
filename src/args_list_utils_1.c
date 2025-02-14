/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:46:44 by rlane             #+#    #+#             */
/*   Updated: 2024/10/18 11:35:21 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg_node	*arg_list_new(char *content, int quote_flag)
{
	t_arg_node	*new;

	new = malloc(sizeof(t_arg_node));
	if (!new)
		return (NULL);
	new->content = content;
	new->quote_flag = quote_flag;
	new->next = NULL;
	return (new);
}

t_arg_node	*arg_list_last(t_arg_node *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	arg_list_free(t_arg_node *head)
{
	t_arg_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->content)
			free(temp->content);
		if (temp)
			free(temp);
	}
}

void	arg_list_add_back(t_arg_node **head, t_arg_node *new)
{
	t_arg_node	*temp;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	args_list_to_array(t_node *node)
{
	t_arg_node	*temp;
	int			i;

	i = 0;
	temp = node->args_list;
	if (!temp)
	{
		node->args = ft_calloc(1, sizeof(char *));
		node->args[0] = NULL;
		return ;
	}
	node->args = ft_calloc(arg_list_size(node->args_list) + 1, sizeof(char *));
	node->quote_flag = ft_calloc(arg_list_size(node->args_list) + 1,
			sizeof(int));
	while (temp)
	{
		node->args[i] = ft_strdup((char *)temp->content);
		node->quote_flag[i] = temp->quote_flag;
		temp = temp->next;
		i++;
	}
	node->args[i] = NULL;
}
