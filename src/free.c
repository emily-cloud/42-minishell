/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:29:03 by rlane             #+#    #+#             */
/*   Updated: 2024/11/10 12:34:37 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env_list(shell->env);
	if (shell)
		free(shell);
}

void	free_nodes(t_node *current)
{
	if (current->left)
		free_nodes(current->left);
	if (current->right)
		free_nodes(current->right);
	if (current->args_list)
		arg_list_free(current->args_list);
	if (current->content)
		free(current->content);
	if (current->args)
		ft_free_array(current->args);
	if (current->quote_flag)
		free(current->quote_flag);
	if (current)
		free(current);
}

void	free_env_list(t_env_node *head)
{
	t_env_node	*current;

	while (head)
	{
		current = head;
		head = head->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
	}
}

void	free_env_node(t_env_node *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}
