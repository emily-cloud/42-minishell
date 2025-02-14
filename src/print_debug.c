/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:17:12 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 14:09:54 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_tree_recursive(t_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	printf(ORANGE "%s" RESET " p:%d\n", node->content, node->presedence);
	if (node->left)
	{
		i = -1;
		while (++i < depth)
			printf("   ");
		printf("L: ");
		print_tree_recursive(node->left, depth + 1);
	}
	if (node->right)
	{
		i = -1;
		while (++i < depth)
			printf("   ");
		printf("R: ");
		print_tree_recursive(node->right, depth + 1);
	}
}

void	print_tree(t_node *root)
{
	printf("\nTree\n");
	print_tree_recursive(root, 0);
	printf("\n");
}

void	print_array(char **array, char *name)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf(ORANGE "%s[%d]: " RESET "%s\n", name, i, array[i]);
		i++;
	}
}

void	print_node_type(t_node *current)
{
	if (current->type == OP_REDIR_IN)
		printf("type: OP_REDIR_IN\n");
	else if (current->type == OP_REDIR_OUT)
		printf("type: OP_REDIR_OUT\n");
	else if (current->type == OP_REDIR_APPEND)
		printf("type: OP_REDIR_APPEND\n");
	else if (current->type == OP_HEREDOC)
		printf("type: OP_HEREDOC\n");
	else if (current->type == DELIMITER)
		printf("type: DELIMITER\n");
	else if (current->type == CMD)
		printf("type: CMD\n");
	else if (current->type == ARG_FILE)
		printf("type: ARG_FILE\n");
	else if (current->type == ASSIGN_VAR)
		printf("type: ASSIGN_VAR\n");
	else if (current->type == SUB_SHELL)
		printf("type: SUB_SHELL\n");
	else if (current->type == OP_AND)
		printf("type: OP_AND\n");
	else if (current->type == OP_OR)
		printf("type: OP_OR\n");
	else if (current->type == FILE_OR_PATH)
		printf("type: FILE_OR_PATH\n");
}

void	print_simple_list(t_node *top)
{
	t_node	*current;

	printf("\nBasic Node List\n");
	current = top;
	while (current)
	{
		printf(ORANGE "content: " RESET "%s\n", current->content);
		printf(ORANGE "formatted args:\n" RESET);
		print_array(current->args, "args");
		if (current->type == OP_PIPE)
			printf("type: OP_PIPE\n");
		else
			print_node_type(current);
		printf("precedence: %d\n", current->presedence);
		if (current->right)
			current = current->right;
		else
			break ;
	}
}

void	print_args_list(t_arg_node *top)
{
	t_arg_node	*current;

	printf("\nArgs List\n");

	current = top;
	while (current)
	{
		printf(ORANGE "content: " RESET "%s\n", current->content);
		printf("quote_flag: %d\n", current->quote_flag);
		if (current->next)
			current = current->next;
		else
			break ;
	}
}*/
