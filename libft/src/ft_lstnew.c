/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:48:25 by rlane             #+#    #+#             */
/*   Updated: 2024/05/03 15:20:18 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a new node.
// The member variable ’content’ is initialized with
// the value of the parameter ’content’. The variable
// ’next’ is initialized to NULL.

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem -> content = content;
	elem -> next = NULL;
	return (elem);
}
/*include <string.h>  // Include for strcmp
int	main(void)
{
	t_list	*element;
	char	*mystring = "Failure is Learning!";

	element = ft_lstnew(mystring);
	if (!element)
	{
		printf("KO: Failed to allocate memory for list element.\n");
		return (1);
	}
	if (strcmp((char *)element->content, mystring) != 0)
	{
		printf("KO: Incorrect content in the list element.\n");
		return (1);
	}
		
	if (element->next != NULL)
	{
		printf("KO: Next should be NULL.\n");
		return (1);
	}
	printf("\n%s\n\n", (char *)element->content);
	printf("OK: Element has correct content and next is NULL.\n");
	free(element);
	return (0);
}*/