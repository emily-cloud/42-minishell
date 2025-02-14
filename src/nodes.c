/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:44 by rlane             #+#    #+#             */
/*   Updated: 2024/11/07 13:35:04 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_op_type(t_node *node)
{
	if (!node->args[0] || node->args[0][0] == '\0')
		return ;
	if (!my_strcmp(node->args[0], "&&") || !my_strcmp(node->args[0], "&"))
		node->type = OP_AND;
	else if (!my_strcmp(node->args[0], "||"))
		node->type = OP_OR;
	else if (!my_strcmp(node->args[0], "|"))
		node->type = OP_PIPE;
	else if (!my_strcmp(node->args[0], ">>"))
		node->type = OP_REDIR_APPEND;
	else if (!my_strcmp(node->args[0], "<<"))
		node->type = OP_HEREDOC;
	else if (!my_strcmp(node->args[0], ">"))
		node->type = OP_REDIR_OUT;
	else if (!my_strcmp(node->args[0], "<"))
		node->type = OP_REDIR_IN;
	else if (node->content[0] == '(')
		node->type = SUB_SHELL;
	else if (node->args[0][0] == '/' || !ft_strncmp(node->args[0], "./", 2) 
		|| node->args[0][ft_strlen(node->args[0]) - 1] == '/')
		node->type = FILE_OR_PATH;
	else if (node->args[1] && !my_strcmp(node->args[1], "="))
		node->type = ASSIGN_VAR;
}

void	set_node_type(char **tokens, int i, t_node *node)
{
	node->type = CMD;
	set_op_type(node);
	if (i == 0)
		return ;
	if (my_strcmp(tokens[i - 1], "<<") == 0)
	{
		if (is_op(tokens[i]) == 0)
			node->type = DELIMITER;
	}
	else if (my_strcmp(tokens[i - 1], "<") == 0 || my_strcmp(tokens[i - 1],
			">") == 0 || my_strcmp(tokens[i - 1], ">>") == 0)
	{
		if (is_op(tokens[i]) == 0)
			node->type = ARG_FILE;
	}
}

void	set_presedence(t_node *node)
{
	if (node->type == OP_AND || node->type == OP_OR)
		node->presedence = 4;
	else if (node->type == OP_PIPE)
		node->presedence = 3;
	else if (node->type == OP_REDIR_OUT || node->type == OP_REDIR_IN
		|| node->type == OP_REDIR_APPEND)
		node->presedence = 2;
	else if (node->type == OP_HEREDOC)
		node->presedence = 1;
}
