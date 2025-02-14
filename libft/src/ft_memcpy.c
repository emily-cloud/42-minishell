/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:01:35 by rlane             #+#    #+#             */
/*   Updated: 2024/10/16 11:57:14 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Casting src to unsigned char* changes pointer type for byte-wise access
// it does not change the data itself, as it must be unalterered (const void).

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*p_src;
	unsigned char		*p_dest;
	size_t				i;

	if (!dest && !src)
		return (dest);
	p_src = (const unsigned char *)src;
	p_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
