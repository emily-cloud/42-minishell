/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:27:32 by rlane             #+#    #+#             */
/*   Updated: 2024/05/01 13:21:48 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_putstr_fd.c"
// #include "ft_putchar_fd.c"

// Outputs the integer ’n’ to the given file descriptor.

void	ft_putnbr_fd(int n, int fd)

{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}

/*
int	main(void)
{
	int	fd;
	int	n = -2147483648;
	fd = open("test.txt", O_RDWR | O_CREAT, 0755);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	ft_putnbr_fd(n, fd);
	if (close(fd) == -1)
	{
		printf("Error closing file\n");
		return (1);
	}
	return (0);
}*/