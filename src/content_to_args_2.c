/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_to_args_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:55:17 by rlane             #+#    #+#             */
/*   Updated: 2024/11/12 14:06:06 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	current_quote;
	int		len;

	len = ft_strlen(str);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	current_quote = 0;
	while (i < len)
	{
		if (!current_quote && (str[i] == '"' || str[i] == '\''))
			current_quote = str[i++];
		else if (current_quote && str[i] == current_quote)
		{
			current_quote = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	fill_arg_helper(t_node *node, int *i, int *len, char *current_quote)
{
	int	end_quote;

	end_quote = 0;
	if (!*current_quote && (node->content[*i + *len] == '"'
			|| node->content[*i + *len] == '\''))
		*current_quote = node->content[*i + *len];
	else if (*current_quote && node->content[*i + *len] == *current_quote)
	{
		if (!(node->content[*i + *len - 1] == *current_quote))
			end_quote = 1;
		*current_quote = 0;
	}
	(*len)++;
	return (end_quote);
}

static void	bracket_counter(char c, int *bracket_count)
{
	if (c == '(')
		(*bracket_count)++;
	else if (c == ')')
		(*bracket_count)--;
}

static void	init_vars(char *current_quote, int *bracket_count, int *end_quote)
{
	*current_quote = 0;
	*bracket_count = 0;
	*end_quote = 0;
}

int	process_arg_content(t_node *node, int *i, int *len)
{
	char	current_quote;
	int		bracket_count;
	int		end_quote;

	init_vars(&current_quote, &bracket_count, &end_quote);
	while (node->content[*i + *len])
	{
		if (!current_quote)
		{
			if ((node->content[*i + *len + 1]
					&& node->content[*i + *len + 1] == '=')
				|| node->content[*i + *len] == '=')
			{
				(*len)++;
				break ;
			}
			bracket_counter(node->content[*i + *len], &bracket_count);
			if ((node->content[*i + *len] == ' ' && !bracket_count)
				|| end_quote)
				break ;
		}
		end_quote = fill_arg_helper(node, i, len, &current_quote);
	}
	return (bracket_count != 0);
}
