/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:01:24 by rlane             #+#    #+#             */
/*   Updated: 2024/09/27 12:40:02 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	else
		return (0);
}

// nptr stands for number pointer (a string representing a num)
int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
	printf("Arguments: a_number_string\n");
	return (-1);
	}

	printf("ft return integer: %d\n", ft_atoi(argv[1]));
	printf("sy return integer: %d\n", atoi(argv[1]));
}*/
