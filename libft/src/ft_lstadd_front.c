/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:48:25 by rlane             #+#    #+#             */
/*   Updated: 2024/05/03 15:20:18 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_lstnew.c"

// Allocates (with malloc(3)) and returns a new node.
// The member variable ’content’ is initialized with
// the value of the parameter ’content’. The variable
// ’next’ is initialized to NULL.
// 1. set new element next adress to point to the start of the existing list
// set the existing list pointer to point to the new element

// t_list **lst is a pointer to a pointer to a t_list node, which allows us
// to change the head tlist object, & dereferencing with *lst is a pointer 
// to a t_list node

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
/*
#include <string.h>  // Include for strcmp
int	main(void)
{
	t_list	*list;
	t_list	*new;
	char	*str1 = "Hello";
	char	*str2 = "World";

	list = ft_lstnew(str1);
	new = ft_lstnew(str2);
	
	printf("\nInitial content: %s\n", (char *) list->content);

	ft_lstadd_front(&list, new);

	printf("\nNew front content: %s\n", (char *) list->content);

	free(list->next);
	free(list);
	return (0);
}*/