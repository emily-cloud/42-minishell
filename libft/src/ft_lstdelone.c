/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufus <rufus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:18:43 by rlane             #+#    #+#             */
/*   Updated: 2024/06/24 19:31:47 by rufus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Takes as a parameter a node and frees the memory ofthe node’s content using 
// the function ’del’ given as a parameter and free the node. 
// The memory of ’next’ must not be freed.

// void del(void *content) {
//     free(content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		if (lst->content != NULL)
		{
			del(lst->content);
			lst->content = NULL;
		}
		free(lst);
		lst = NULL;
	}
}
