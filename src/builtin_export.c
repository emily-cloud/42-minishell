/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:23:57 by hai               #+#    #+#             */
/*   Updated: 2024/11/11 15:42:38 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*copy_list(t_env_node *env)
{
	t_env_node	*copy_head;

	copy_head = NULL;
	while (env)
	{
		if (!copy_head)
		{
			copy_head = create_node((char *[]){env->name, env->value},
					env->exported);
		}
		else
			add_env_node((char *[]){env->name, env->value}, copy_head,
				env->exported);
		env = env->next;
	}
	return (copy_head);
}

void	sort_print_list(t_shell *shell)
{
	t_env_node	*copied_list;
	t_env_node	*current;

	copied_list = copy_list(shell->env);
	sort_list(&copied_list);
	current = copied_list;
	while (current)
	{
		if (current->name && (current->exported == 1 || current->exported == 2))
		{
			if (current->value && current->value[0] != '\0')
				ft_printf("declare-x %s=\"%s\"\n" RESET,
					current->name, current->value);
			else if (current->exported == 2)
				ft_printf("declare -x %s\n", current->name);
			else if (current->exported == 1)
				ft_printf("declare -x %s=\"\"\n", current->name);
		}
		current = current->next;
	}
	free_env_list(copied_list);
}

void	check_export_args(t_node *node)
{
	if (node->args[2] == NULL)
	{
		if (get_env_node(node->shell->env, node->args[1]) == NULL)
			add_env_node((char *[]){node->args[1], ""},
				node->shell->env, EXPORTED_ONLY);
		else
			get_env_node(node->shell->env, node->args[1])->exported = 1;
	}
	else if ((node->args[2][0] == '=' && node->args[3] == NULL))
	{
		if (get_env_node(node->shell->env, node->args[1]) == NULL)
			add_env_node((char *[]){node->args[1], ""},
				node->shell->env, EXPORTED);
		else
			get_env_node(node->shell->env, node->args[1])->exported = 1;
	}
	else if ((node->args[2][0] == '=') && (node->args[3]))
		reset_or_add_env_var(node, node->args[1], node->args[3], EXPORTED);
	else
	{
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		set_last_exit_status(node, 1);
	}
}

void	cmd_export(t_node *node)
{
	if (node->args[1] != NULL && node->args[1][0] != '\0')
	{
		if (!check_var_name(node->args[1]))
		{
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			set_last_exit_status(node, 1);
			return ;
		}
		if ((node->args[2] && node->args[2][0] != '=')
			|| (node->args[1][0] == '=' && !node->args[2]))
		{
			set_last_exit_status(node, 0);
			return ;
		}
		check_export_args(node);
	}
	else
		sort_print_list(node->shell);
}
