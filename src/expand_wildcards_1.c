/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:18 by rlane             #+#    #+#             */
/*   Updated: 2024/10/16 16:02:47 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_exec_ls_node(t_shell *shell, int fd[2])
{
	t_node		*ls_node;

	ls_node = init_node(shell);
	ls_node->args = malloc(sizeof(char *) * 2);
	ls_node->args[0] = ft_strdup("ls");
	ls_node->args[1] = NULL;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	call_external_cmd(ls_node, NULL);
	free_nodes(ls_node);
	exit(EXIT_SUCCESS);
}

void	get_ls_list(t_arg_node **ls_list, t_shell *shell)
{
	int			fd[2];
	char		*line;
	pid_t		pid;

	pipe(fd);
	pid = fork_and_check_pid();
	if (pid == 0)
		make_exec_ls_node(shell, fd);
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		line = get_next_line(fd[0]);
		while (line)
		{
			line[ft_strlen(line) - 1] = '\0';
			arg_list_add_back(ls_list, arg_list_new(ft_strdup(line), 0));
			free(line);
			line = get_next_line(fd[0]);
		}
		close(fd[0]);
		dup2(shell->original_stdout, STDOUT_FILENO);
		dup2(shell->original_stdin, STDIN_FILENO);
	}
}

int	count_star(char const *s)
{
	size_t		i;
	size_t		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			count++;
			i++;
			continue ;
		}
		while (s[i] && s[i] != '*')
			i++;
	}
	return (count);
}

static int	substr_len(const char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	return (j);
}

// Helper function to process a substring between asterisks

int	star_process_substring(char **array, const char *s, size_t *i,
	size_t *string)
{
	size_t	j;

	j = substr_len(s, '*', *i);
	array[*string] = ft_substr(s, *i, j);
	if (array[*string] == NULL)
		return (0);
	(*string)++;
	*i += j;
	return (1);
}
