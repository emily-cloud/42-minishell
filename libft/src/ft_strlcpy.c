/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:49:59 by rlane             #+#    #+#             */
/*   Updated: 2024/04/24 11:38:07 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)src));
}

// Will NOT compile on 42 systems!! it needs a BSD compiler for strlcpy
// this one works : https://www.online-cpp.com/online_c_compiler
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	*src = "abcdefghijklmnopqrstuvxyz";
	char	dst[100];
	char	std_dst[100];
	size_t	size = 4;
	size_t	len_dst;
	size_t	len_dst_std;

	len_dst = ft_strlcpy(dst, src, size);
	len_dst_std = strlcpy(std_dst, src, size);

	printf("src = %s\n", src);
	printf("buffer len = %zu\n", size);
	printf("ft_strlcpy dst = %s\n", dst);
	printf("return = %zu\n\n", len_dst);
	printf("std_strlcpy dst = %s\n", std_dst);
	printf("return = %zu\n\n", len_dst_std);
	return (0);
}*/
