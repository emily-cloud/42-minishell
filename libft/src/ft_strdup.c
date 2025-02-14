/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:24:47 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:54:37 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include "ft_strlcpy.c"
//#include "ft_strlen.c"

// returns a pointer to a new string which is
// a duplicate of the string s.  Memory for the new string is
// obtained with malloc(3), and can be freed with free(3).

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	dest = ft_calloc(1, s_len + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, s_len + 1);
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Argument: string_to_duplicate\n");
		printf("Return: duplicated string address\n");
		return (-1);
	}
	printf("ft return: %s\n", ft_strdup(argv[1]));
	printf("sy return: %s\n", strdup(argv[1]));
	return (0);
}*/