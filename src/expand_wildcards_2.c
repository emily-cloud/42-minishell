/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:18 by rlane             #+#    #+#             */
/*   Updated: 2024/10/17 10:52:59 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function to handle special cases (start and end asterisks)

int	star_handle_special_cases(char **array, const char *s, size_t *i,
	size_t *string)
{
	if (*i == 0 && s[0] == '*')
	{
		array[*string] = ft_strdup("");
		if (!array[*string])
			return (0);
		(*string)++;
		(*i)++;
	}
	else if (*i > 0 && s[*i - 1] == '*' && !s[*i])
	{
		array[*string] = ft_strdup("");
		if (!array[*string])
			return (0);
		(*string)++;
	}
	return (1);
}

char	**star_split_segment(char const *s)
{
	char	**array;
	size_t	i;
	size_t	string;

	i = 0;
	string = 0;
	array = ft_calloc(1, sizeof(char *) * (count_star(s) + 2));
	if (!array)
		return (NULL);
	if (!star_handle_special_cases(array, s, &i, &string))
		return (ft_free_array(array));
	while (s[i])
	{
		while (s[i] == '*' && s[i])
			i++;
		if (!s[i])
			break ;
		if (!star_process_substring(array, s, &i, &string))
			return (ft_free_array(array));
	}
	if (!star_handle_special_cases(array, s, &i, &string))
		return (ft_free_array(array));
	array[string] = NULL;
	return (array);
}

t_wc_vars	*init_wc_var(void)
{
	t_wc_vars	*wcv;

	wcv = malloc(sizeof(t_wc_vars));
	wcv->temp = NULL;
	wcv->next_temp = NULL;
	wcv->filtered_list = NULL;
	wcv->prev = NULL;
	wcv->ls_list = NULL;
	return (wcv);
}

static void	fill_segments(t_node *node, t_wc_vars *wcv)
{
	char			**segments;

	segments = star_split_segment((char *)wcv->temp->content);
	wcv->filtered_list = filter_ls_list(wcv->ls_list, segments);
	if (wcv->filtered_list)
	{
		if (wcv->prev)
			wcv->prev->next = wcv->filtered_list;
		else
			node->args_list = wcv->filtered_list;
		wcv->prev = arg_list_last(wcv->filtered_list);
		if (wcv->next_temp)
			arg_list_last(wcv->filtered_list)->next = wcv->next_temp;
		free(wcv->temp->content);
		free(wcv->temp);
	}
	else
		wcv->prev = wcv->temp;
	if (segments)
		ft_free_array(segments);
}

void	expand_wildcards(t_node *node)
{
	t_wc_vars		*wcv;

	wcv = init_wc_var();
	get_ls_list(&wcv->ls_list, node->shell);
	wcv->temp = node->args_list;
	if (node->type == OP_HEREDOC && node->right)
		node->right->args_list->quote_flag = 1;
	while (wcv->temp)
	{
		wcv->next_temp = wcv->temp->next;
		if (ft_strchr((char *)wcv->temp->content, '*')
			&& wcv->temp->quote_flag == 0)
			fill_segments(node, wcv);
		else
		{
			wcv->prev = wcv->temp;
		}
		wcv->temp = wcv->next_temp;
	}
	if (wcv->ls_list)
		arg_list_free(wcv->ls_list);
	free(wcv);
}
