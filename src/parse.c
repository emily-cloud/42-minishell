/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:05:01 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 14:13:49 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print_args_list(new->args_list); //debug

t_node	*init_pre_node(char *token, t_shell *shell,
						int prev_is_redirection)
{
	t_node	*new;

	new = init_node(shell);
	new->content = ft_strdup(token);
	content_to_args(new);
	if (ft_strchr(token, '*') && !prev_is_redirection)
		expand_wildcards(new);
	args_list_to_array(new);
	if (!prev_is_redirection)
		expand_dollar_args(new);
	return (new);
}

t_node	*fill_nodes(char **tokens, t_shell *shell)
{
	t_node	*top;
	t_node	*current;
	t_node	*new;
	int		i;
	int		prev_is_redirection;

	top = NULL;
	i = -1;
	while (tokens[++i])
	{
		prev_is_redirection = (i > 0 && (my_strcmp(tokens[i - 1], "<<") == 0
					|| my_strcmp(tokens[i - 1], "&&") == 0));
		new = init_pre_node(tokens[i], shell, prev_is_redirection);
		set_node_type(tokens, i, new);
		set_presedence(new);
		if (!top)
			top = new;
		else
			current->right = new;
		current = new;
	}
	return (top);
}

void	parse_line(char *line, t_shell *shell)
{
	char	**tokens;
	t_node	*tree_top;

	tokens = ft_calloc(count_tokens(line) + 1, sizeof(char *));
	tokenize(line, &tokens);
	if (!tokens)
		return ;
	tree_top = fill_nodes(tokens, shell);
	if (input_error_check(tree_top))
	{
		free_nodes(tree_top);
		ft_free_array(tokens);
		return ;
	}
	tree_top = build_tree(tree_top);
	ft_free_array(tokens);
	exec_tree(tree_top);
	free_nodes(tree_top);
	return ;
}
	//print_tree(tree_top); //debug
	//print_simple_list(tree_top); //debug
