/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:25:34 by rlane             #+#    #+#             */
/*   Updated: 2024/04/23 17:40:10 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	p_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p_s[i] == (unsigned char)c)
			return ((void *)&p_s[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>	// includes atoi function
#include <string.h>	 
int	main(int argc, char *argv[])
{
	size_t	num_bytes;
	char	char_to_find;
	char	*returned;
	char	*sy_returned;

	if (argc != 4)
	{
		printf("args: string char_to_find bytes_to_check");
		return (-1);
	}
	num_bytes = atoi(argv[3]);
	char_to_find = argv[2][0];
	returned = (char *)ft_memchr(argv[1], char_to_find, num_bytes);
	sy_returned = (char *)memchr(argv[1], char_to_find, num_bytes);
	if (returned != NULL)
		printf("ft_return from found char onwards: %s\n", returned);
	else
		printf("ft_not found!\n");
	if (sy_returned != NULL)
		printf("sy_return from found char onwards: %s\n", returned);
	else
		printf("sy_not found!\n");
       return (0);
}*/
