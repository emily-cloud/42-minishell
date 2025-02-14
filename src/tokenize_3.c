/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:43:07 by rlane             #+#    #+#             */
/*   Updated: 2024/10/16 09:52:41 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function modifies the token by removing the `\n` escape sequence.
static void	tokendup(char **token, int j)
{
	char	*temp;
	char	*new_token;

	temp = ft_strdup(*token);
	if (!temp)
		return ;
	temp[j] = '\0';
	new_token = ft_strjoin(temp, *token + j + 2);
	free(*token);
	*token = new_token;
	free(temp);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	copy_len;
	char	*dup;

	len = ft_strlen(s);
	if (n > len)
		copy_len = len;
	else
		copy_len = n;
	dup = malloc(copy_len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, copy_len);
	dup[copy_len] = '\0';
	return (dup);
}

void	check_space(char *temp, char *space_loc)
{
	if (!temp || !space_loc)
	{
		free(temp);
		return ;
	}
}

static void	cat_str_to_token(char **token, char **str)
{
	char	*new_token;
	char	*space_loc;
	char	*temp;
	int		i;

	if (!token || !*token || !str || !*str)
		return ;
	i = 0;
	while ((*str)[i] && (*str)[i] != ' ')
		i++;
	temp = ft_strndup(*str, i);
	space_loc = ft_strchr(*str, ' ');
	check_space(temp, space_loc);
	new_token = ft_strjoin(*token, space_loc);
	if (!new_token)
	{
		free(temp);
		return ;
	}
	free(*str);
	*str = temp;
	free(*token);
	*token = new_token;
}

void	organize_tokens(char ***tokens)
{
	int	i;
	int	j;

	if (!tokens || !*tokens)
		return ;
	i = -1;
	while ((*tokens)[++i])
	{
		j = 0;
		while ((*tokens)[i][j])
		{
			if ((*tokens)[i][j] == '\\' && (*tokens)[i][j + 1] == 'n')
				tokendup(&(*tokens)[i], j);
			j++;
		}
		if ((ft_strncmp((*tokens)[i], "echo", 4) == 0) && (*tokens)[i + 1]
			&& (my_strcmp((*tokens)[i + 1], ">") == 0
			|| my_strcmp((*tokens)[i + 1], ">>") == 0
				|| my_strcmp((*tokens)[i + 1], "<") == 0)
			&& (*tokens)[i + 2])
		{
			if (ft_strchr((*tokens)[i + 2], ' '))
				cat_str_to_token(&((*tokens)[i]), &((*tokens)[i + 2]));
		}
	}
}
