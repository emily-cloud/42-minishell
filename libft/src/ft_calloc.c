/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:48:09 by rlane             #+#    #+#             */
/*   Updated: 2024/04/24 19:20:41 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//  nmemb is number of members, size is number of bytes per member
//  first if prevents over allocation of memeory

#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*buffer;
	size_t			i;

	if ((size > 0) && (nmemb > SIZE_MAX / size))
		return (NULL);
	buffer = malloc(nmemb * size * sizeof(unsigned char));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		buffer[i] = '\0';
		i++;
	}
	return ((void *)buffer);
}
