/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:49:59 by rlane             #+#    #+#             */
/*   Updated: 2024/04/24 11:42:51 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// append at most (size - strlen(dst) - 1)
// return initial length of dst plus the length of src

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (size <= dst_len)
	{
		dst_len = size;
		return (dst_len + src_len);
	}
	i = 0;
	while ((i < (size - dst_len - 1)) && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// Will NOT compile on 42 systems!! it needs a BSD compiler for strlcat
// this one works : https://www.online-cpp.com/online_c_compiler
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	const char	*src = "abcdefghi";
	size_t	size = 7;
	char	*dst_initial_string = "1234";
	char	*dst;
	char	*dst_std;

	dst = malloc(size * sizeof(char));
	if (!dst)
		return (1);
	strcpy(dst, dst_initial_string);
	
	dst_std = malloc(size * sizeof(char));
	if (!dst_std)
	{
		free (dst);
		return (1);
	}
	strcpy(dst_std, dst_initial_string);

	size_t	len_dst;
	size_t	len_dst_std;

	printf("dst = %s\n", dst);
	len_dst = ft_strlcat(dst, src, size);
	len_dst_std = strlcat(std_dst, src, size);

	printf("src = %s\n", src);
	printf("buffer size = %zu\n\n", size);
	printf("ft_strlcat dst = %s\n", dst);
	printf("return = %zu\n\n", len_dst);
	printf("std_strlcat dst = %s\n", dst_std);
	printf("return = %zu\n\n", len_dst_std);
	
	free (dst);
	free (dst_std);
	
	return (0);
}*/
