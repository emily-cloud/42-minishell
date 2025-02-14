/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_to_args_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:55:17 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 14:24:20 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char c, int *quote_flag)
{
	if (c == '\'')
		*quote_flag = 1;
	if (c == '"')
		*quote_flag = 2;
}

void	fill_arg(t_node *node, int *i)
{
	int		start;
	int		len;
	char	*arg;
	char	*cleaned_arg;
	int		quote_flag;

	start = *i;
	len = 0;
	quote_flag = 0;
	if (process_arg_content(node, i, &len))
	{
		write_error_message(node, "(");
		arg = ft_strdup("");
	}
	else
		arg = ft_substr(node->content, start, len);
	check_quotes(arg[0], &quote_flag);
	cleaned_arg = trim_quotes(arg);
	arg_list_add_back(&node->args_list, arg_list_new(cleaned_arg, quote_flag));
	free(arg);
	if (len > 0)
		*i += len;
	else
		(*i)++;
}

void	content_to_args(t_node *node)
{
	int	i;

	i = 0;
	if (!node->content)
	{
		node->args_list = NULL;
		return ;
	}
	while (node->content[i])
	{
		while (node->content[i] == ' ')
			i++;
		if (node->content[i])
			fill_arg(node, &i);
	}
}
