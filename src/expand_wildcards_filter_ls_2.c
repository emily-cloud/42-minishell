/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_filter_ls_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:18 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:19:06 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_last_segment(t_filter_data *data, t_arg_node *current,
		char *copy)
{
	if ((data->segments[data->array_len - 1][0] != '\0' && copy[0] == '\0')
		|| data->segments[data->array_len - 1][0] == '\0')
	{
		arg_list_add_back(&data->filtered_list,
			arg_list_new(ft_strdup(current->content), 0));
	}
}

void	process_node(t_filter_data *data, t_arg_node *current)
{
	char	*copy;
	int		i;

	copy = ft_strdup(current->content);
	i = 0;
	while (data->segments[i] && copy)
	{
		if (!process_segment(data, &copy, i))
			break ;
		i++;
		if (data->segments[i] == NULL)
			handle_last_segment(data, current, copy);
	}
	if (copy)
		free(copy);
}

t_arg_node	*filter_ls_list(t_arg_node *ls_list, char **segments)
{
	t_filter_data	data;
	t_arg_node		*current;

	init_filter_data(&data, ls_list, segments);
	if (handle_empty_segments(&data))
		return (data.filtered_list);
	current = ls_list;
	while (current)
	{
		process_node(&data, current);
		current = current->next;
	}
	return (data.filtered_list);
}
