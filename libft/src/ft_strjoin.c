/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:26:04 by rlane             #+#    #+#             */
/*   Updated: 2024/04/25 08:13:45 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include "ft_strlen.c"
#include "ft_strlcpy.c"
#include "ft_strlcat.c"*/

// concatenate two strings

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len1 + len2 + 1);
	return (str);
}
/*
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Arguments: string1 string2\n");
		printf("Returns: concatenated string\n");
		return (-1);
	}
	printf("Concatenated: %s\n", ft_strjoin(argv[1], argv[2]));
	return (0);
}*/
