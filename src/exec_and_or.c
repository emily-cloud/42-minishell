/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:44:23 by rlane             #+#    #+#             */
/*   Updated: 2024/11/05 14:29:01 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recurse_expand_dollar(t_node *node)
{
	expand_dollar_args(node);
	if (node->right)
		recurse_expand_dollar(node->right);
	if (node->left)
		recurse_expand_dollar(node->left);
}

void	exec_and(t_node *node)
{
	if (!node->left || !node->right)
		return ;
	if (my_strcmp(node->left->args[0], "false") == 0)
	{
		set_last_exit_status(node, 1);
		return ;
	}
	exec_tree(node->left);
	recurse_expand_dollar(node->right);
	exec_tree(node->right);
}

void	exec_or(t_node *node)
{
	if (!node->left || !node->right)
		return ;
	if (my_strcmp(node->left->args[0], "true") == 0)
	{
		set_last_exit_status(node, 0);
		return ;
	}
	exec_tree(node->left);
	if (node->shell->last_exit_status != 0)
		exec_tree(node->right);
}
