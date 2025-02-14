/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:58:16 by rlane             #+#    #+#             */
/*   Updated: 2024/05/02 08:23:51 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a string
// representing the integer received as an argument.
// Negative numbers must be handled.

static size_t	ft_count_elements(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_num_to_str(int nb, size_t i, char *s)
{
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	while (i > 0)
	{
		i--;
		s[i] = (nb % 10) + '0';
		nb /= 10;
	}
}

// min_int is a bloolean to know whether we have recieved minimum int
char	*ft_itoa(int n)
{
	char	*str;
	size_t	str_len;
	int		min_int;

	min_int = 0;
	if (n == -2147483648)
	{
		n++;
		min_int = 1;
	}
	str_len = ft_count_elements(n);
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_num_to_str(n, str_len, str);
	if (n < 0)
		str[0] = '-';
	str[str_len] = '\0';
	if (min_int)
		str[str_len - 1] = '8';
	return (str);
}
/*
int	main(void)
{
	int	nb;
	
	nb = 2147483647;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

	nb = -2147483648;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

	nb = -1;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

	nb = 1;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));


	nb = -1234567890;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

	nb = 1234567890;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

	nb = 0;
	printf("interger  : %d\n", nb);
	printf("return str: %s\n\n", ft_itoa(nb));

}*/