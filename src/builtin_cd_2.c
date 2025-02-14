/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:37:21 by hai               #+#    #+#             */
/*   Updated: 2024/10/15 18:24:21 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_path(char **path, t_env_node *env, char *name)
{
	t_env_node	*temp;

	temp = env;
	*path = NULL;
	while (temp)
	{
		if (!my_strcmp(temp->name, name))
		{
			*path = ft_strdup(temp->value);
			if (*path == NULL)
			{
				perror("Memory allocation failed");
			}
			break ;
		}
		temp = temp->next;
	}
	if (*path == NULL)
	{
		printf("Environment variable '%s' not found\n", name);
	}
}

void	ch_path(char *path, t_node *node)
{
	char	*old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		free(old_pwd);
		set_last_exit_status(node, 1);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("Error getting current working directory\n", STDERR_FILENO);
		free(old_pwd);
		return ;
	}
	set_env_value(node->shell->env, "OLDPWD", old_pwd, 1);
	set_env_value(node->shell->env, "PWD", cwd, 1);
	free (old_pwd);
}

void	ch_home_sub(char *path, t_node *node)
{
	char	*temp;
	char	*new_path;
	char	*home_path;

	temp = path + 1;
	home_path = NULL;
	new_path = NULL;
	assign_path(&home_path, node->shell->env, "HOME");
	new_path = malloc(ft_strlen(path) + ft_strlen(temp) + 1);
	if (!new_path)
	{
		perror("Memory allocation failed");
		free(home_path);
		return ;
	}
	ft_strlcpy(new_path, home_path, ft_strlen(home_path) + 1);
	ft_strlcat(new_path, temp, ft_strlen(new_path) + ft_strlen(temp) + 1);
	ch_path(new_path, node);
	free(new_path);
	free(home_path);
}

void	ch_home(t_node *node)
{
	char	*home_path;

	assign_path(&home_path, node->shell->env, "HOME");
	if (home_path == NULL)
	{
		ft_putstr_fd("HOME environment variable not set\n", STDERR_FILENO);
		return ;
	}
	ch_path(home_path, node);
	free(home_path);
}

void	ch_oldpwd(t_node *node)
{
	char	*oldpwd;

	assign_path(&oldpwd, node->shell->env, "OLDPWD");
	ch_path(oldpwd, node);
	print_variable(node->shell->env, "PWD");
	free(oldpwd);
}
