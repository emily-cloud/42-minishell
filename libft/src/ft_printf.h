/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:19:08 by rlane             #+#    #+#             */
/*   Updated: 2024/09/04 10:46:20 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

void	ft_putchar(char c);
size_t	ft_strlen(const char *str);
void	ft_putstr(char *s);
size_t	ft_putnbr_hex_count(unsigned int nb, char *charset);
size_t	ft_putnbr_pointer_count(uintptr_t nb, char *charset);
size_t	ft_putnbr_count(int n);
size_t	ft_putnbr_unsigned_count(unsigned int n);
size_t	ft_print_char(int c);
size_t	ft_print_string(char *str);
size_t	ft_print_address(void *address);
size_t	ft_format_handler(char format, va_list args);
int		ft_printf(const char *str, ...);
char	**ft_free(char **array, size_t string_count);

#endif
