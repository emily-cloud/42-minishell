/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:12:59 by rlane             #+#    #+#             */
/*   Updated: 2024/04/25 11:55:49 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include "ft_strlen.c"
//#include "ft_strchr.c"
//#include "ft_strlcpy.c"

// Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
// specified in ’set’ removed from the beginning and the end of the string

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	start;
	size_t	end;
	size_t	trimmed_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_len = end - start;
	trimmed_str = malloc(trimmed_len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, &s1[start], trimmed_len + 1);
	return (trimmed_str);
}
/*
int	main(int argc, char **argv)
{
	char	*str;
	char	*set;

	if (argc != 3)
	{
		printf("Arguments: string set_of_chars_to_trim\n");
		return (-1);
	}
	printf("Return: %s\n", ft_strtrim(argv[1], argv[2]));
	return (0);
}*/