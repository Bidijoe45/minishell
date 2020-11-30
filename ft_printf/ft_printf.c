/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:24:39 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/04 16:30:56 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_specific(char type, va_list list, t_flags *flags)
{
	if (flags->precision != -1 && flags->zero == 1)
		flags->zero = -1;
	if (flags->minus == 1 && flags->zero == 1)
		flags->zero = -1;
	if (type == 's')
		ft_print_str(list, flags);
	else if (type == 'c')
		ft_print_char((char)va_arg(list, int), flags);
	else if (type == '%')
		ft_print_char('%', flags);
	else if (type == 'd' || type == 'i')
		ft_print_int(va_arg(list, int), flags);
	else if (type == 'p')
		ft_print_pointer(va_arg(list, unsigned long), flags);
	else if (type == 'u')
		ft_print_uint(va_arg(list, unsigned int), flags);
	else if (type == 'x')
		ft_print_x_low(va_arg(list, unsigned int), flags);
	else if (type == 'X')
		ft_print_x_up(va_arg(list, unsigned int), flags);
}

void	ft_init_flags(t_flags *flags)
{
	flags->width = 0;
	flags->precision = -1;
	flags->minus = -1;
	flags->zero = -1;
}

void	ft_init(t_flags *flags, int *i)
{
	flags->written = 0;
	*i = 0;
}

int		ft_printf(const char *str, ...)
{
	va_list args;
	t_flags flags;
	int		i;

	va_start(args, str);
	ft_init(&flags, &i);
	ft_init_flags(&flags);
	while (str[i])
		if (str[i] == '%' && str[i + 1])
		{
			i += ft_enable_flags(str + i + 1, &flags, args);
			if (i == -1)
				return (flags.written);
			ft_init_flags(&flags);
		}
		else if (str[i] != '%')
		{
			write(1, &str[i], 1);
			(flags.written)++;
			i++;
		}
		else
			i++;
	va_end(args);
	return (flags.written);
}
