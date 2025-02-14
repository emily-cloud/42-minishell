/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufus <rufus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:58:41 by rlane             #+#    #+#             */
/*   Updated: 2024/06/24 19:32:22 by rufus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// take format character and choose output function
// return character count increase
size_t	ft_format_handler(char format, va_list args)
{
	if (format == 'c')
		return (ft_print_char((char)va_arg(args, int)));
	if (format == 's')
		return (ft_print_string(va_arg(args, char *)));
	if (format == 's')
		return (ft_print_string(va_arg (args, char *)));
	if (format == 'd')
		return (ft_putnbr_count(va_arg(args, int)));
	if (format == 'i')
		return (ft_putnbr_count(va_arg(args, int)));
	if (format == 'u')
		return (ft_putnbr_unsigned_count(va_arg(args, unsigned int)));
	if (format == 'x')
		return (ft_putnbr_hex_count(va_arg(args, uintptr_t),
				"0123456789abcdef"));
	if (format == 'X')
		return (ft_putnbr_hex_count(va_arg(args, uintptr_t),
				"0123456789ABCDEF"));
	if (format == 'p')
		return (ft_print_address(va_arg(args, void *)));
	if (format == '%')
		return (ft_print_char('%'));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	size_t	string_index;
	size_t	print_count;
	va_list	args;

	if (!string)
		return (-1);
	va_start(args, string);
	string_index = 0;
	print_count = 0;
	while (string[string_index])
	{
		if (string[string_index] == '%' && string[string_index + 1])
		{
			string_index++;
			print_count += ft_format_handler(string[string_index], args);
			string_index++;
		}
		else
		{
			ft_putchar(string[string_index]);
			print_count++;
			string_index++;
		}
	}
	return ((print_count));
}
