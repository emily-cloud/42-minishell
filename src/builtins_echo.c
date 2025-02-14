/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:35:47 by rlane             #+#    #+#             */
/*   Updated: 2024/11/05 14:45:45 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_node *node)
{
	int		i;

	i = 1;
	while (node->args[i])
	{
		if (i > 1 && node->args[i][0] != '='
			&& node->args[i - 1][0] != '=')
			ft_printf(" ");
		ft_printf("%s", node->args[i]);
		i++;
	}
	printf("\n");
}

static void	put_n(char *args, char **str)
{
	int		j;
	int		len;

	j = 1;
	len = ft_strlen(args);
	*str = malloc(len + 1);
	(*str)[0] = '-';
	while (j < len)
	{
		(*str)[j] = 'n';
		j++;
	}
	(*str)[j] = '\0';
}

static int	n_check(t_node *node)
{
	int		i;
	char	*str;

	i = 1;
	while (node->args[i] && node->args[i][0] == '-')
	{
		put_n(node->args[i], &str);
		if (!my_strcmp(node->args[i], str))
		{
			i++;
			free(str);
		}
		else
		{
			free(str);
			break ;
		}
	}
	return (i);
}

static void	print_args(t_node *node, int i, int j)
{
	while (node->args[i])
	{
		if (i > j)
			ft_printf(" ");
		ft_printf("%s", node->args[i]);
		i++;
	}
}

void	cmd_echo(t_node *node)
{
	int		i;
	int		j;

	i = 1;
	if (!node->args[1])
	{
		ft_printf("\n");
		return ;
	}
	expand_tilda(node);
	if (ft_strncmp(node->args[1], "-n", 2))
		print_echo(node);
	else
	{
		i = n_check(node);
		j = i;
		if (node->args[i] == NULL)
			return ;
		print_args(node, i, j);
	}
}
