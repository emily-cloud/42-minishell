/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:01:58 by rlane             #+#    #+#             */
/*   Updated: 2024/06/12 20:01:58 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_lstnew.c"
// #include "ft_lstadd_front.c"
// #include "ft_lstsize.c"
// #include "ft_lstlast.c"
// #include "ft_lstadd_back.c"
// #include "ft_lstdelone.c"

// Deletes and frees the given node and every successor of that node, using the
// function ’del’ and free(3).
// Finally, the pointer to the list must be set to NULL.
// CANNOT be used on node part way thru list or it causes dangling mem-location

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;	

	while (*lst)
	{
		temp = (*lst)-> next ;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
/*
void del(void *content) 
{
    free(content);
}

void	ft_print_list(t_list *temp_list)
{
	int	node_count = 0;
	if (temp_list == NULL)
	{
		printf("There is no such list\n\n");
		return ;
	}
	printf("\n\nTest List\n\n");
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
	t_list	*altered_list;
	t_list	*temp_list;

	test_list = NULL;

	test_list = ft_lstnew(content1);
	ft_lstadd_back(&test_list, ft_lstnew(content2));
	ft_lstadd_back(&test_list, ft_lstnew(content3));
	ft_lstadd_front(&test_list, ft_lstnew(content4));

	temp_list = test_list;

	ft_print_list(temp_list);

	temp_list = test_list;
	
	ft_lstclear(&temp_list, &del);

	printf("\n\nAttempt to print deleted List:\n\n");

	ft_print_list(temp_list);
	
	return (0);
}*/