/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 08:19:37 by rlane             #+#    #+#             */
/*   Updated: 2024/05/01 13:18:14 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_putchar_fd.c"

// Outputs the string ’s’ to the given file descriptor.

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

/*
int	main(void)
{
	int	fd;
	char	s[] = "Hello World!";
	fd = open("test.txt", O_RDWR | O_CREAT, 0755);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	ft_putstr_fd(s, fd);
	if (close(fd) == -1)
	{
		printf("Error closing file\n");
		return (1);
	}
	return (0);
}*/