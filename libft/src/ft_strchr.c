/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:56:20 by rlane             #+#    #+#             */
/*   Updated: 2024/05/03 11:12:45 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The  strchr() function returns a pointer to the first occurrence of the
// character c in the string s.

char	*ft_strchr(const char *s, int c)
{
	char	c_c;
	int		i;

	c_c = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c_c)
			return ((char *)&s[i]);
		i++;
	}
	if (c_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char char_to_find;

	if (argc != 3)
	{
		printf("Arguments: string_to_search char_to_find\n");
		printf("Returns: string from found point\n");
		return (-1);
	}

	char_to_find = argv[2][0];
	printf("return: %s\n", ft_strchr((const char *)argv[1], char_to_find));
	return (0);
}*/