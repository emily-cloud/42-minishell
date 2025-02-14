/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:55:10 by rlane             #+#    #+#             */
/*   Updated: 2024/04/23 17:40:10 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (p_s1[i] != p_s2[i])
			return ((unsigned char)p_s1[i] - (unsigned char)p_s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>     // includes atoi function
#include <string.h>     // include for memcmp

int	main(int argc, char *argv[]) 
{
    if (argc < 4) 
    {
        printf("Usage: %s string1 string2 num\n", argv[0]);
        return 1;
    }
    size_t num = (size_t)atoi(argv[3]);  // Number of bytes to compare
    printf("ft_return: %d\n", ft_memcmp(argv[1], argv[2], num)); 
    printf("sy_return: %d\n", memcmp(argv[1], argv[2], num)); 
    return 0;
}*/
