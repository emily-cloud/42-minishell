/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:13:04 by rlane             #+#    #+#             */
/*   Updated: 2024/11/07 11:50:00 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// replaces first occurrence of target in string with replace

char	*string_replace(char *string, char *target, char *replace)
{
	char	*result;
	char	*pos;
	size_t	target_len;
	size_t	replace_len;
	size_t	new_len;

	result = NULL;
	if (!string || !target || !replace)
		return (NULL);
	target_len = ft_strlen(target);
	replace_len = ft_strlen(replace);
	pos = ft_strnstr(string, target, ft_strlen(string));
	if (!pos)
		return (ft_strdup(string));
	new_len = ft_strlen(string) - target_len + replace_len;
	result = ft_calloc(new_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, string, pos - string);
	ft_memcpy(result + (pos - string), replace, replace_len);
	ft_memcpy(result + (pos - string) + replace_len, pos + target_len,
		ft_strlen(pos + target_len) + 1);
	return (result);
}

int	replace_variable(t_node *node, int arg, int i, int j)
{
	char		*var_name;
	char		*var_value;
	char		*new_content;
	t_env_node	*env_node;

	var_name = ft_substr(node->args[arg], i + 1, j - 1);
	if (!var_name)
		return (-1);
	env_node = get_env_node(node->shell->env, var_name);
	if (env_node)
		var_value = env_node->value;
	else
		var_value = "";
	free(var_name);
	var_name = ft_substr(node->args[arg], i, j);
	if (!var_name)
		return (-1);
	new_content = string_replace(node->args[arg], var_name, var_value);
	free(var_name);
	if (!new_content)
		return (-1);
	free(node->args[arg]);
	node->args[arg] = new_content;
	return (ft_strlen(var_value));
}

void	update_qt_state(char c, int *in_single_qt, int *in_double_qt)
{
	if (c == '\'' && !(*in_double_qt))
		*in_single_qt = !(*in_single_qt);
	else if (c == '\"' && !(*in_single_qt))
		*in_double_qt = !(*in_double_qt);
}
