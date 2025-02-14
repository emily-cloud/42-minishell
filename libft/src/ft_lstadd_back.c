/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:44:09 by rlane             #+#    #+#             */
/*   Updated: 2024/05/03 15:20:18 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds the node ’new’ at the end of the list.

// t_list **lst is a pointer to a pointer to a t_list node, which allows us
// to change the head tlist object, & dereferencing with *lst is a pointer 
// to a t_list node

// if there is a pointer to a NULL list then the new becomes the new list

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp -> next = new;
	}
}
