/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:43:07 by rlane             #+#    #+#             */
/*   Updated: 2024/11/11 14:53:29 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_tokens(const char *s, size_t *i, int *open_quote,
		int *open_bracket)
{
	size_t		j;
	char		*token;

	j = 0;
	while (ft_isspace(s[*i]))
		(*i)++;
	while (s[*i + j])
	{
		*open_quote = handle_quotes(s[*i + j], *open_quote, 0);
		*open_bracket = handle_brackets(s[*i + j], *open_bracket);
		if (!*open_quote && !*open_bracket && is_op(s + *i + j))
			break ;
		if (j > 0 && s[*i + j] == '(' && !*open_quote && !*open_bracket)
			break ;
		j++;
	}
	token = ft_substr(s, *i, j);
	*i += j;
	return (token);
}

static t_token_vars	init_token_vars(void)
{
	t_token_vars	vars;

	vars.open_quote = 0;
	vars.open_bracket = 0;
	vars.string = 0;
	vars.i = 0;
	vars.op_len = 0;
	return (vars);
}

static int	check_quote_skip_spaces(t_token_vars vars, const char *s)
{
	if (!vars.open_quote)
	{
		while (ft_isspace(s[vars.i]))
			vars.i++;
		if (!s[vars.i])
			return (0);
	}
	return (1);
}

void	tokenize(const char *s, char ***tokens)
{
	t_token_vars	vars;

	vars = init_token_vars();
	while (s[vars.i])
	{
		if (!check_quote_skip_spaces(vars, s))
			break ;
		vars.op_len = 0;
		if (!vars.open_quote)
			vars.op_len = is_op(s + vars.i);
		if (vars.op_len)
		{
			(*tokens)[vars.string++] = ft_substr(s, vars.i, vars.op_len);
			vars.i += vars.op_len;
		}
		else
			(*tokens)[vars.string++] = fill_tokens(s, &vars.i,
					&vars.open_quote, &vars.open_bracket);
	}
	(*tokens)[vars.string] = NULL;
	organize_tokens(tokens);
}
