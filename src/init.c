/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:07:04 by rlane             #+#    #+#             */
/*   Updated: 2024/11/11 16:24:58 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp, int export_status)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = NULL;
	set_env_list(shell, envp, export_status);
	shell->last_exit_status = 0;
	shell->original_stdin = STDIN_FILENO;
	shell->original_stdout = STDOUT_FILENO;
	shell->original_stderr = STDERR_FILENO;
	return (shell);
}

t_node	*init_node(t_shell *shell)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->shell = shell;
	node->type = 0;
	node->content = NULL;
	node->presedence = 0;
	node->left = NULL;
	node->right = NULL;
	node->args_list = NULL;
	node->args = NULL;
	node->quote_flag = NULL;
	node->active_fd_out = 1;
	return (node);
}

void	set_last_exit_status(t_node *node, int status)
{
	char	*status_str;

	node->shell->last_exit_status = status;
	status_str = ft_itoa(status);
	reset_or_add_env_var(node, "?", status_str, NOT_EXPORTED);
	free(status_str);
}

void	set_last_exit_status_exit_success(t_node *node, int status)
{
	char	*status_str;

	node->shell->last_exit_status = status;
	status_str = ft_itoa(status);
	reset_or_add_env_var(node, "?", status_str, NOT_EXPORTED);
	free(status_str);
	exit(EXIT_SUCCESS);
}
