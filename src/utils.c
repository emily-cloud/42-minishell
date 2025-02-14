/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:39:30 by rlane             #+#    #+#             */
/*   Updated: 2024/10/18 15:52:09 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	reset_stin_stout(t_node *node)
{
	if (node->shell->original_stdin != STDIN_FILENO)
	{
		dup2(node->shell->original_stdin, STDIN_FILENO);
	}
	if (node->shell->original_stdout != STDOUT_FILENO)
	{
		dup2(node->shell->original_stdout, STDOUT_FILENO);
	}
}

int	my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int	is_all_spaces(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len--)
	{
		if (!ft_isspace(line[len]))
			return (1);
	}
	return (0);
}

int	strlen_cmp(char *str1, char *str2)
{
	int	cmp_len;

	if (ft_strlen(str1) >= ft_strlen(str2))
		cmp_len = ft_strlen(str1);
	else
		cmp_len = ft_strlen(str2);
	return (cmp_len);
}
