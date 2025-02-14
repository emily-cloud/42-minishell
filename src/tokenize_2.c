/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:43:07 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 16:37:26 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(const char *s)
{
	char	**ops;
	int		i;

	ops = (char *[9]){"<<", ">>", "||", "|", "<", ">", "&&", "&", NULL};
	i = 0;
	while (ops[i])
	{
		if (ft_strncmp(s, ops[i], ft_strlen(ops[i])) == 0)
			return (ft_strlen(ops[i]));
		i++;
	}
	return (0);
}

size_t	count_tokens(const char *s)
{
	size_t	count;
	size_t	i;
	int		op_len;

	count = 0;
	i = 0;
	while (s[i])
	{
		op_len = is_op(s + i);
		if (op_len)
			i += op_len;
		else if (s[i] == '(' || s[i] == ')')
			i++;
		else
			while (s[i] && !is_op(s + i) && s[i] != ')')
				i++;
		count++;
	}
	return (count);
}

int	handle_quotes(char c, int open_quote, int reset)
{
	static int		single_quote_open;
	static int		double_quote_open;

	if (reset)
	{
		single_quote_open = 0;
		double_quote_open = 0;
		return (0);
	}
	if (c == '"')
	{
		if (single_quote_open)
			return (open_quote);
		double_quote_open = !double_quote_open;
	}
	if (c == '\'')
	{
		if (double_quote_open)
			return (open_quote);
		single_quote_open = !single_quote_open;
	}
	open_quote = single_quote_open || double_quote_open;
	return (open_quote);
}

int	handle_brackets(char c, int open_bracket)
{
	if (c == '(')
		open_bracket++;
	if (c == ')')
		open_bracket--;
	return (open_bracket);
}
