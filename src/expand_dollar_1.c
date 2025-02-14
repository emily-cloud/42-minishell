/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:13:04 by rlane             #+#    #+#             */
/*   Updated: 2024/11/07 11:14:09 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_last_exit_status(t_node *node, int arg, char *new_content)
{
	new_content = string_replace(node->args[arg], "$?",
			get_env_node(node->shell->env, "?")->value);
	if (new_content)
	{
		free(node->args[arg]);
		node->args[arg] = new_content;
	}
	return (1);
}

int	process_dollar(t_node *node, int arg, int i)
{
	int		ret;
	int		j;
	char	*new_content;

	new_content = NULL;
	if (node->args[arg][i] == '$')
	{
		if (!node->args[arg][i + 1])
			return (i);
		j = 1;
		while (node->args[arg][i + j] && (ft_isalnum(node->args[arg][i + j])
				|| node->args[arg][i + j] == '_'))
			j++;
		if (node->args[arg][i + j] == '?')
			ret = handle_last_exit_status(node, arg, new_content);
		else
			ret = replace_variable(node, arg, i, j);
		if (ret == -1)
			return (-1);
		i += ret;
	}
	return (i);
}

int	should_process_dollar(char *content, int i)
{
	if (content[i] != '$' || !content[i + 1])
		return (0);
	if (ft_isspace(content[i + 1]) || content[i + 1] == '\0')
		return (0);
	if (content[i + 1] != '$' && !ft_isspace(content[i + 1]))
		return (1);
	return (0);
}

void	expand_dollar_args(t_node *node)
{
	int		i;
	int		arg;
	int		arg_count;

	arg_count = ft_count_array(node->args);
	arg = 0;
	while (arg < arg_count)
	{
		i = 0;
		while (!(node->quote_flag[arg] == 1) && node->args[arg][i])
		{
			if (should_process_dollar(node->args[arg], i))
			{
				i = process_dollar(node, arg, i);
				if (i == -1)
				{
					set_last_exit_status(node, 0);
					return ;
				}
				continue ;
			}
			i++;
		}
		arg++;
	}
}
