/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufus <rufus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:55:10 by rlane             #+#    #+#             */
/*   Updated: 2024/06/24 19:33:42 by rufus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two strings up to a specified number of characters.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if the first
 *  `n` characters of `s1` are found, respectively, to be less than, to match,
 *  or be greater than the first `n` characters of `s2`.
 */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && (i < n) && (s1[i] == s2[i]))
		i++;
	if (i > (n - 1))
		i = n - 1;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
#include <stdlib.h>	// includes atoi function
#include <string.h>	// include for strncmp

int	main(int argc, char *argv[])
{	
	if (argc < 4) 
	{	
		printf("Usage: %s string1 string2 num\n", argv[0]);
		return 1;
	}
	size_t num = (size_t)atoi(argv[3]);
	printf("ft_return: %d\n", ft_strncmp(argv[1], argv[2], num));
	printf("sy_return: %d\n", strncmp(argv[1], argv[2], num));
	return (0);
}*/
