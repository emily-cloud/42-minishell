/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:38:38 by rlane             #+#    #+#             */
/*   Updated: 2024/11/11 12:08:28 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env_to_array(t_env_node *env)
{
	t_env_node	*current;
	char		**new_env;
	char		*temp;
	int			i;

	current = env;
	i = count_env_nodes(env);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (current)
	{
		if (current->exported)
		{
			temp = ft_strjoin(current->name, "=");
			if (current->value)
				new_env[++i] = ft_strjoin(temp, current->value);
			else
				new_env[++i] = ft_strdup(temp);
			free(temp);
		}
		current = current->next;
	}
	new_env[++i] = NULL;
	return (new_env);
}

void	handle_error_codes_exit(t_node *node, char *path, char **env)
{
	dup2(STDOUT_FILENO, STDERR_FILENO);
	if (errno == EACCES)
	{
		printf ("%s: Permission denied\n", node->args[0]);
		set_last_exit_status(node, 126);
	}
	else if (errno == ENOENT)
	{
		printf ("%s: No such file or directory\n", node->args[0]);
		set_last_exit_status(node, 127);
	}
	else if (errno == ENOEXEC)
	{
		printf ("%s: Exec format error. Binary file not executable.\n",
			node->args[0]);
		set_last_exit_status(node, 126);
	}
	else
	{
		printf ("%s: Unknown error\n", node->args[0]);
		set_last_exit_status(node, 1);
	}
	free (path);
	ft_free_array (env);
	exit (EXIT_FAILURE);
}

char	*find_full_path(t_node *node)
{
	t_env_node	*path_node;
	char		**path_dirs;
	char		*full_path;
	char		*temp;
	int			i;

	path_node = get_env_node(node->shell->env, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	path_dirs = ft_split(path_node->value, ':');
	if (!path_dirs)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(temp, node->args[0]);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (ft_free_array(path_dirs), full_path);
		free(full_path);
	}
	ft_free_array(path_dirs);
	return (NULL);
}

void	reset_sigs_find_path_execve(t_node *node, char *path)
{
	char	*full_path;
	char	**new_env;

	full_path = NULL;
	new_env = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	new_env = convert_env_to_array(node->shell->env);
	if (path == NULL)
		full_path = find_full_path(node);
	else
		full_path = path;
	if (!full_path || full_path[0] == '\0')
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		set_last_exit_status(node, 127);
		ft_free_array(new_env);
		exit(127);
	}
	else if (execve(full_path, node->args, new_env) == -1)
		handle_error_codes_exit(node, full_path, new_env);
}

void	call_external_cmd(t_node *node, char *path)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork_and_check_pid();
	if (pid == 0)
	{
		reset_sigs_find_path_execve(node, path);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_last_exit_status(node, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				g_sigint_received = 1;
			else if (WTERMSIG(status) == SIGQUIT)
				write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			set_last_exit_status(node, 128 + WTERMSIG(status));
		}
	}
}
