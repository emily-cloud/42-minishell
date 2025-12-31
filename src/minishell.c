/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:04:10 by rlane             #+#    #+#             */
/*   Updated: 2024/10/18 15:54:29 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_loop(t_shell *shell)
{
	char		*line;

	line = NULL;
	while (1)
	{
		g_sigint_received = 0;
		if (g_sigint_received)
		{
			if (line)
				free(line);
			continue ;
		}
		line = readline("🦀-> ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (*line && is_all_spaces(line))
		{
			add_history(line);
			parse_line(line, shell);
		}
		free(line);
	}
}
// printf("\nWelcome to " ORANGE " 🦀 MINISHELL 🦀\n\n" RESET
//"Type " ORANGE "help" RESET " if you need it!\n" RESET);
// printf("🦀 Bye Bye!\n");

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	if (argc > 1 || argv[1])
	{
		printf("input is not supported\n");
		return (1);
	}
	init_signal_handlers();
	shell = init_shell(envp, EXPORTED);
	input_loop(shell);
	free_shell(shell);
	rl_clear_history();
	//clear_history();
	printf("exit\n");
	return (0);
}
