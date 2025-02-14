/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:47:14 by rlane             #+#    #+#             */
/*   Updated: 2024/11/08 14:03:49 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(t_node *node)
{
	t_env_node	*env_node;

	env_node = get_env_node(node->shell->env, "PWD");
	printf("%s\n", env_node->value);
}

void	cmd_help(void)
{
	printf(GREEN "\n🦀 DON'T PANIC 🦀\n\n" RESET);
	printf(ORANGE "MINISHELL is here to help u shake ur thang.\n" RESET);
	printf("My shell capacities may be mini but you");
	printf("can BASH away like there's no tomorrow...\n\n");
	printf(ORANGE "Here are my handcrafted commands:\n\n" RESET);
	printf(ORANGE "help   " RESET "display this help\n");
	printf(ORANGE "pwd    " RESET "show present working directory\n");
	printf(ORANGE "exit   " RESET "exit the shell\n");
	printf(ORANGE "env    " RESET "display the environment variables\n");
	printf(ORANGE "unset  " RESET "remove an environment variable\n");
	printf(ORANGE "echo   " RESET "display a line of text\n");
	printf(ORANGE "cd     " RESET "change the current directory\n");
	printf(ORANGE "export " RESET "set an environment variable\n");
	printf(ORANGE ">      " RESET "redirect output to a file\n");
	printf(ORANGE ">>     " RESET "append output to a file\n");
	printf(ORANGE "<      " RESET "redirect input from a file\n");
	printf(ORANGE "<<     " RESET "redirect input from a here document\n");
	printf(ORANGE "|      " RESET "pipe output to another command\n");
	printf(ORANGE "$?     " RESET "display exit status of last command\n");
	printf(ORANGE "&&     " RESET "logical AND\n");
	printf(ORANGE "||     " RESET "logical OR\n");
	printf(ORANGE "( ... )" RESET "run command in sub shell\n\n");
}

void	cmd_env(t_node *head)
{
	t_env_node	*current;

	if (head->args[1])
	{
		ft_putstr_fd("too many argment\n", STDERR_FILENO);
		set_last_exit_status(head, 1);
		return ;
	}
	current = head->shell->env;
	while (current)
	{
		if (current->name && current->exported == 1)
		{
			if (current->value)
				ft_printf("%s=%s\n", current->name, current->value);
			else if (current->value == (void *)0)
				ft_printf("%s=\n", current->name);
		}
		current = current->next;
	}
}

void	cmd_unset(t_node *node)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!node->args[1] || node->args[2])
		return ;
	prev = NULL;
	current = node->shell->env;
	while (current)
	{
		if (!my_strcmp(current->name, node->args[1]))
		{
			if (prev)
				prev->next = current->next;
			else
				node->shell->env = current->next;
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
