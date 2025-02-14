/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:51:57 by rlane             #+#    #+#             */
/*   Updated: 2024/05/01 12:45:10 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_putstr_fd.c"
// #include "ft_putchar_fd.c"

// Outputs the string ’s’ to the given file descriptor followed by a newline.

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
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
	ft_putendl_fd(s, fd);
	if (close(fd) == -1)
	{
		printf("Error closing file\n");
		return (1);
	}
	return (0);
}*/