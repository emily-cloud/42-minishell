/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:38 by rlane             #+#    #+#             */
/*   Updated: 2024/05/01 11:51:11 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the character ’c’ to the given file
// descriptor.

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	int	fd;
	char	c = 'x';
	fd = open("test.txt", O_RDWR | O_CREAT, 0755);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	ft_putchar_fd(c, fd);
	if (close(fd) == -1)
	{
		printf("Error closing file\n");
		return (1);
	}
	return (0);
}*/