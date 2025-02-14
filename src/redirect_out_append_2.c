/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_append2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:26:37 by hai               #+#    #+#             */
/*   Updated: 2024/10/16 10:27:02 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd_an_dup2(int fd, int fd2, t_node *current)
{
	if (fd < 0)
	{
		ft_putstr_fd(current->right->args[0], STDERR_FILENO);
		set_last_exit_status(current, 1);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, fd2) < 0)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
}

int	fork_and_check_pid(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
