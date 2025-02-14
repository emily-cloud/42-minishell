/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:07:52 by hai               #+#    #+#             */
/*   Updated: 2024/10/17 10:53:37 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_star(char const *s)
{
	size_t		i;
	size_t		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			count++;
			i++;
			continue ;
		}
		while (s[i] && s[i] != '*')
			i++;
	}
	return (count);
}

static int	substr_len(const char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	return (j);
}

static void	add_blank_to_array(char **array, int *string, int *i)
{
	array[*string] = ft_strdup("");
	if (!array[*string])
	{
		ft_free_array(array);
		return ;
	}
	(*string)++;
	(*i)++;
}

static void	loop_through_string(char const *s, char **array, 
	int *string, int *i)
{
	int		j;

	while (s[*i])
	{
		while (s[*i] == '*' && s[*i])
			i++;
		if (!s[*i])
			break ;
		j = substr_len(s, '*', *i);
		array[*string] = ft_substr(s, *i, j);
		if (array[*string] == NULL)
		{
			ft_free_array(array);
			return ;
		}
		(*string)++;
		*i += j;
	}
}

char	**split_segments(char const *s, char c)
{
	char		**array;
	int			i;
	int			string;

	array = ft_calloc(1, sizeof(char *) * (count_star(s) + 2));
	if (!array)
		return (NULL);
	string = 0;
	i = 0;
	if (s[0] == c)
		add_blank_to_array(array, &string, &i);
	loop_through_string(s, array, &string, &i);
	if (i > 0 && s[i - 1] == c)
	{
		array[string] = ft_strdup("");
		if (!array[string])
			return (ft_free_array(array));
		string++;
	}
	array[string] = NULL;
	return (array);
}
