/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:23:14 by rlane             #+#    #+#             */
/*   Updated: 2024/11/07 13:33:28 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_last_exit_status_string(char **str, t_node *node)
{
	char	*new_content;

	new_content = string_replace(*str, "$?",
			get_env_node(node->shell->env, "?")->value);
	if (new_content)
	{
		free(*str);
		*str = new_content;
	}
	return (1);
}

int	replace_variable_string(char **str, t_node *node, int i, int j)
{
	char		*var_name;
	char		*var_value;
	char		*new_content;
	t_env_node	*env_node;

	var_name = ft_substr(*str, i + 1, j - 1);
	if (!var_name)
		return (-1);
	env_node = get_env_node(node->shell->env, var_name);
	if (env_node)
		var_value = env_node->value;
	else
		var_value = "";
	free(var_name);
	var_name = ft_substr(*str, i, j);
	if (!var_name)
		return (-1);
	new_content = string_replace(*str, var_name, var_value);
	free(var_name);
	if (!new_content)
		return (-1);
	free(*str);
	*str = new_content;
	return (ft_strlen(var_value));
}

int	process_dollar_string(char **str, t_node *node, int i, int in_single_quote)
{
	int	ret;
	int	j;

	if ((*str)[i] == '$' && !in_single_quote)
	{
		if (!(*str)[i + 1])
			return (i);
		j = 1;
		while ((*str)[i + j] && (ft_isalnum((*str)[i + j])
				|| (*str)[i + j] == '_'))
			j++;
		if ((*str)[i + j] == '?')
			ret = handle_last_exit_status_string(str, node);
		else
			ret = replace_variable_string(str, node, i, j);
		if (ret == -1)
			return (-1);
		i += ret;
	}
	return (i);
}

int	should_process_dollar_string(char *content, int i, int in_single_qt,
	int in_double_qt)
{
	if (content[i] != '$' || !content[i + 1])
		return (0);
	if (in_single_qt)
		return (0);
	if (in_double_qt || 
		(!in_double_qt && content[i + 1] != ' ' && content[i + 1] != '$'))
		return (1);
	return (0);
}

char	*expand_dollar_string(t_node *node, char *str)
{
	int	i;
	int	in_single_qt;
	int	in_double_qt;

	if (!node || !str || !node->shell)
		return (NULL);
	in_single_qt = 0;
	in_double_qt = 0;
	i = 0;
	while (str[i])
	{
		update_qt_state(str[i], &in_single_qt, &in_double_qt);
		if (should_process_dollar_string(str, i, in_single_qt, in_double_qt))
		{
			i = process_dollar_string(&str, node, i, in_single_qt);
			if (i == -1)
			{
				set_last_exit_status(node, 0);
				return (NULL);
			}
			continue ;
		}
		i++;
	}
	return (str);
}
