/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:02:42 by rlane             #+#    #+#             */
/*   Updated: 2024/11/11 15:58:17 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_name(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	exec_assign_var(t_node *node)
{
	char	**env_args;
	int		exp_ind;

	exp_ind = 0;
	if (!my_strcmp(node->args[0], "export"))
		exp_ind = 1;
	if (!check_var_name(node->args[exp_ind]))
	{
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		set_last_exit_status(node, 1);
		return ;
	}
	if (get_env_node(node->shell->env, node->args[exp_ind])
		&& node->args[exp_ind + 2])
		return (set_env_value(node->shell->env, node->args[exp_ind],
				node->args[exp_ind + 2], exp_ind));
	env_args = ft_calloc(3, sizeof(char *));
	if (node->args[exp_ind])
		env_args[0] = ft_strdup(node->args[exp_ind]);
	if (node->args[exp_ind + 2])
		env_args[1] = ft_strdup(node->args[exp_ind + 2]);
	add_env_node(env_args, node->shell->env, exp_ind);
	ft_free_array(env_args);
}

void	check_and_execute_file(t_node *node)
{
	char	*path;
	t_node	*exec_node;
	int		i;

	if (!access(node->args[0], X_OK))
	{
		path = ft_strdup(node->args[0]);
		exec_node = init_node(node->shell);
		exec_node->args = malloc(sizeof(char *) 
				* (ft_count_array(node->args) + 1));
		exec_node->args[0] = ft_strdup(ft_strrchr(node->args[0], '/') + 1);
		i = 0;
		while (node->args[++i])
			exec_node->args[i] = ft_strdup(node->args[i]);
		exec_node->args[i] = NULL;
		call_external_cmd(exec_node, path);
		ft_free_array(exec_node->args);
		free(exec_node);
		free(path);
	}
	else
	{
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		set_last_exit_status(node, 126);
	}
}

void	exec_path_search(t_node *node)
{
	struct stat		path_stat;

	if (stat(node->args[0], &path_stat) == 0)
	{
		set_last_exit_status(node, 0);
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			set_last_exit_status(node, 126);
		}
		else if (S_ISREG(path_stat.st_mode))
		{
			check_and_execute_file(node);
		}
	}
	else
	{
		ft_putstr_fd(node->args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		set_last_exit_status(node, 127);
	}
}
