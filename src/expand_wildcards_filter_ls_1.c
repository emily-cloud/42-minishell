/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_filter_ls_1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:18 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:18:40 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_ls_list(t_arg_node **dest, t_arg_node *src)
{
	t_arg_node	*current;

	current = src;
	while (current)
	{
		arg_list_add_back(dest,
			arg_list_new(ft_strdup(current->content), 0));
		current = current->next;
	}
}

void	init_filter_data(t_filter_data *data, t_arg_node *ls_list, 
	char **segments)
{
	data->ls_list = ls_list;
	data->filtered_list = NULL;
	data->segments = segments;
	data->array_len = 0;
	while (segments[data->array_len] != NULL)
		data->array_len++;
}

int	handle_empty_segments(t_filter_data *data)
{
	if (data->segments[0][0] == '\0' && data->segments[1][0] == '\0')
	{
		copy_ls_list(&data->filtered_list, data->ls_list);
		return (1);
	}
	return (0);
}

int	process_segment(t_filter_data *data, char **copy, int i)
{
	char	*temp1;
	char	*temp2;

	if (i == 0 && data->segments[i][0] != '\0'
		&& ft_strncmp(*copy, data->segments[i],
			ft_strlen(data->segments[i])) != 0)
		return (0);
	temp1 = ft_strnstr(*copy, data->segments[i], ft_strlen(*copy));
	if (temp1)
	{
		temp2 = ft_strdup(temp1 + ft_strlen(data->segments[i]));
		free(*copy);
		*copy = temp2;
		if (data->segments[i + 1] == NULL && (*copy)[0] != '\0')
			return (handle_last_occurrence(data, copy, i));
	}
	else
		return (0);
	return (1);
}

int	handle_last_occurrence(t_filter_data *data, char **copy, int i)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strnstr(*copy, data->segments[i], ft_strlen(*copy));
	if (temp1)
	{
		temp2 = ft_strdup(temp1 + ft_strlen(data->segments[i]));
		free(*copy);
		*copy = temp2;
		return (1);
	}
	return (0);
}
