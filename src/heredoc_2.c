/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:42:48 by rlane             #+#    #+#             */
/*   Updated: 2024/10/18 09:41:21 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*my_strndup(char *s, size_t n)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n > len)
		n = len;
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	my_strncpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

char	*get_var_value(char *var_name, t_node *node)
{
	t_env_node	*current;

	current = get_env_node(node->shell->env, var_name);
	if (current->value == NULL)
		return (NULL);
	return (current->value);
}

size_t	get_var_length(char *input, size_t *i)
{
	size_t	var_start;
	size_t	var_len;

	(*i)++;
	var_start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	var_len = *i - var_start;
	return (var_len);
}

size_t	handle_var_expansion(char *input, size_t var_len,
			size_t i, t_node *node)
{
	char	*var_name;
	char	*var_value;
	size_t	result_len;

	result_len = 0;
	var_name = my_strndup(input + (i - var_len), var_len);
	var_value = get_var_value(var_name, node);
	if (var_value)
		result_len += ft_strlen(var_value);
	free(var_name);
	return (result_len);
}
