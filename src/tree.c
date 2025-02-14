/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:01:59 by hai               #+#    #+#             */
/*   Updated: 2024/11/12 14:14:46 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_tree2(t_node **top, t_node **root,
		t_node **prev, t_node **prev_root)
{
	t_node	*current;
	int		highest_pres_val;

	current = (*top)->right;
	highest_pres_val = (*top)->presedence;
	while (current)
	{
		if (current->presedence >= highest_pres_val)
		{
			highest_pres_val = current->presedence;
			*root = current;
			*prev_root = *prev;
		}
		*prev = current;
		current = current->right;
	}
}

t_node	*build_tree(t_node *top)
{
	t_node	*root;
	t_node	*prev;
	t_node	*prev_root;

	if (!top)
		return (NULL);
	if (!top->right)
		return (top);
	root = top;
	prev = top;
	prev_root = NULL;
	build_tree2(&top, &root, &prev, &prev_root);
	if (prev_root)
		prev_root->right = NULL;
	if (root != top)
		root->left = build_tree(top);
	if (root->right)
		root->right = build_tree(root->right);
	return (root);
}

void	exec_tree2(t_node *node)
{
	if (node->type == OP_REDIR_OUT || node->type == OP_REDIR_APPEND)
	{
		exec_redir_out_append(node, RESET_STATIC);
		exec_redir_out_append(node, 0);
	}
	else if (node->type == OP_REDIR_IN)
	{
		exec_redir_in(node, RESET_STATIC);
		exec_redir_in(node, 0);
	}
	else if (node->type == OP_HEREDOC)
		exec_heredoc(node);
	else if (node->type == FILE_OR_PATH)
		exec_path_search(node);
}

void	exec_tree(t_node *node)
{
	if (node)
	{
		set_last_exit_status(node, 0);
		if (node->type == ASSIGN_VAR)
			exec_assign_var(node);
		else if (node->type == CMD)
			exec_cmd(node);
		else if (node->type == OP_AND)
			exec_and(node);
		else if (node->type == OP_OR)
			exec_or(node);
		else if (node->type == OP_PIPE)
			exec_pipe(node);
		else if (node->type == OP_REDIR_OUT || node->type == OP_REDIR_APPEND
			|| node->type == OP_REDIR_IN || node->type == OP_HEREDOC
			|| node->type == FILE_OR_PATH)
			exec_tree2(node);
		else if (node->type == SUB_SHELL)
			exec_sub_shell(node);
		else
		{
			ft_putstr_fd("Unknown node type\n", STDERR_FILENO);
			set_last_exit_status(node, 1);
		}
	}
}
