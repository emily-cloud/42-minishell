/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:54:58 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:54:58 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include "ft_strlen.c"

//#include "ft_strdup.c"

// create a substring of length len using string and start location

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = ft_strdup("");
		return (substr);
	}
	if ((s_len - start) < len)
		len = s_len - start;
	substr = ft_calloc(1, (len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int	main(int argc, char **argv)
{
	char *substr;

	if (argc != 4)
	{
		printf("Arguments: string start length\n");
		return (-1);
	}
	substr = ft_substr(argv[1], atoi(argv[2]), atoi(argv[3]));
	printf("Substring: %s\n", substr);
	free(substr);
		return (0);	
}*/
