/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:57:00 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:55:15 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns an array of strings obtained by 
// splitting ’s’ using the character ’c’ as a delimiter. The array must end
// with a NULL pointer.

//only counts on the first char that is not a delimiter of each substring

static size_t	ft_count_strings(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free (array);
	return (NULL);
}

static size_t	ft_substr_len(const char *s, char c, size_t i)
{
	size_t	j;

	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	string;

	array = ft_calloc(1, sizeof(char *) * (ft_count_strings(s, c) + 1));
	if (!array)
		return (NULL);
	string = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = ft_substr_len(s, c, i);
		array[string] = ft_substr(s, i, j);
		if (array[string] == NULL)
			return (ft_free_array(array));
		string++;
		i += j;
	}
	array[string] = NULL;
	return (array);
}

/*
int	main(int argc, char **argv)
{
	size_t	count;
	size_t	i = 0;
	char	**split_str;

	if (argc != 3)
	{
		printf("Arguments: string char_delimiter\n");
		return (-1);
	}
	count = ft_count_strings(argv[1], argv[2][0]);
	split_str = ft_split(argv[1], argv[2][0]);
	while(i < count)
	{
		printf("%s\n", (char *)split_str[i]);
		i++;
	}
	return (0);
}*/