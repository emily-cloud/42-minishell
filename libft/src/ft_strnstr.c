/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:25:21 by rlane             #+#    #+#             */
/*   Updated: 2024/09/17 13:43:39 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function locates the first occurrence of the null-terminated string 
 * 'little' in the string 'big', where not more than 'len' characters are 
 * searched. Characters that appear after a '\0' character are not searched.
 *
 * @param big The main string to be searched.
 * @param little The substring to search for within 'big'.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first occurrence of 'little' in 'big', or NULL if 
 *         'little' is not found within the first 'len' characters of 'big'.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (j < little_len && (i + j < len))
		{
			if (big[i + j] != little[j])
				break ;
			if (j == little_len - 1)
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>

char *strnstr(const char *big, const char *little, size_t len);

int main(int argc, char *argv[])
{
    size_t num;
    char *result_ft;

    if (argc < 4)
    {
        printf("Usage: %s big_string little_string num\n", argv[0]);
        return 1;
    }

    num = (size_t)atoi(argv[3]);
    result_ft = strnstr(argv[1], argv[2], num);

    if (result_ft)
    {
        printf("ft_strnstr: Found at position: %ld\n", result_ft - argv[1]);
        printf("ft_strnstr: from found position: %s\n", result_ft);
    }
    else
    {
        printf("ft_strnstr: Not found\n");
    }

    return 0;
}*/
