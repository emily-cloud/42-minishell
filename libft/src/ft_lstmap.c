/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:50:20 by rlane             #+#    #+#             */
/*   Updated: 2024/05/03 15:20:18 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_lstnew.c"
// #include "ft_lstadd_front.c"
// #include "ft_lstsize.c"
// #include "ft_lstlast.c"
// #include "ft_lstadd_back.c"
// #include "ft_lstdelone.c"
// #include "ft_lstclear.c"
// #include "ft_lstiter.c"

// Iterates the list ’lst’ and applies the function ’f’ on the content of each
// node. Creates a newlist resulting of the successive applications of the 
// function ’f’. The ’del’ function is used todelete the content of a node 
// if needed.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*temp;
	void	*mapped_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	temp = lst;
	while (temp)
	{
		mapped_content = f(temp -> content);
		new_node = ft_lstnew(mapped_content);
		if (!new_node)
		{
			free(mapped_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		temp = temp -> next;
	}
	return (new_list);
}
/*
void del(void *content) {
    free(content);
}

void *f(void *content) {
    int *result = malloc(sizeof(int));
    if (result == NULL) 
        return NULL;
    *result = 2 * *(int *)content;  // Dereference, multiply, and store
    return result;  // Return the pointer to the new data
}

void	ft_print_list(t_list *temp_list)
{
	int	node_count = 0;
	if (temp_list == NULL)
	{
		printf("There is no such list\n\n");
		return ;
	}
	while (temp_list)
	{
		printf("node %d - adr %p - content %d - next adr %p\n\n",
			node_count, temp_list, *(int *)(temp_list->content),
			temp_list -> next);
		temp_list = temp_list -> next;
		node_count++;
	}
}
int	main(void)
{
	int *content1 = malloc(sizeof(int));
	int *content2 = malloc(sizeof(int));
	int *content3 = malloc(sizeof(int));
	int *content4 = malloc(sizeof(int));
	*content1 = 1;
	*content2 = 2;
	*content3 = 3;
	*content4 = 0;
	

	t_list	*test_list;
	t_list	*mapped_list;
	t_list	*temp_list;

	test_list = NULL;

	test_list = ft_lstnew(content1);
	ft_lstadd_back(&test_list, ft_lstnew(content2));
	ft_lstadd_back(&test_list, ft_lstnew(content3));
	ft_lstadd_front(&test_list, ft_lstnew(content4));

	temp_list = test_list;

	printf("\n\nTest List:\n\n");

	ft_print_list(temp_list);

	temp_list = test_list;
	
	mapped_list = ft_lstmap(test_list, &f, &del);

	
	printf("\n\nMapped List (function (content * 2)):\n\n");

	ft_print_list(mapped_list);
	
	return (0);
}*/