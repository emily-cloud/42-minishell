/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:29:30 by rlane             #+#    #+#             */
/*   Updated: 2024/05/01 13:06:09 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_strlen.c"

// Applies the function f to each character of the
// string s, passing its index as the first argument
// and the character itself as the second. A new
// string is created (using malloc(3)) to collect the
// results from the successive applications of f.

/*
char	tester(unsigned int i, char c)
{
	char	result;

	result = c + i;
	return (result);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*dest;

	len = ft_strlen(s);
	dest = malloc(sizeof(unsigned char) * (len + 1));
	while (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main(void)
{
	char *s = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
	// expect aplhabet as return, test function loops and adds 1 every time
	
	char *result = ft_strmapi(s, tester);
	if (result) 
	{
        printf("%s\n", result);
        free(result);
	} else {
        printf("Memory allocation failed.\n");
	}

    return (0);
}*/