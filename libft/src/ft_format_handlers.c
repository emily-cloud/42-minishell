/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:56:23 by rlane             #+#    #+#             */
/*   Updated: 2024/06/04 12:11:25 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// print single char as int to output and returns 1 to the char count
size_t	ft_print_char(int c)
{
	ft_putchar(c);
	return (1);
}

// print char string to output and returns strlen to char count
size_t	ft_print_string(char *str)
{
	if (str == NULL)
		return (ft_print_string("(null)"));
	ft_putstr(str);
	return (ft_strlen(str));
}

size_t	ft_print_int(int n)
{
	if (n == -2147483648)
		return (ft_print_string("-2147483648"));
	return (ft_putnbr_count(n));
}

size_t	ft_print_address(void *address)
{
	uintptr_t	n;

	if (address == NULL)
		return (ft_print_string("(nil)"));
	n = (uintptr_t)address;
	ft_putstr("0x");
	return (2 + ft_putnbr_pointer_count(n, "0123456789abcdef"));
}
