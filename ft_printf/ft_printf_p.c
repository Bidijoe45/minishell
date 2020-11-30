/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 10:18:51 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/22 15:02:04 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_normal(char *str, int len, t_flags *flags)
{
	flags->written += write(1, "0x", 2);
	flags->written += write(1, str, len);
}

void	ft_print_precision(char *str, t_flags *flags)
{
	if (flags->width > 0 && flags->precision > 0 &&
			flags->width < flags->precision)
		flags->width = -1;
	if (flags->width > 0 && flags->minus == -1)
		flags->written += ft_print_blank(flags->width - ft_strlen(str) -
				(flags->precision > 0 ? 2 : 1), 0);
	flags->written += write(1, "0x", 2);
	flags->written += ft_print_blank(flags->precision - ft_strlen(str), 1);
	if (flags->precision > 0)
		flags->written += write(1, str, ft_strlen(str));
}

void	ft_print_pointer(unsigned long address, t_flags *flags)
{
	char	*str;
	int		len;

	str = ft_itoa_base(address, "0123456789abcdef", 16);
	len = ft_strlen(str);
	if (flags->precision != -1)
		ft_print_precision(str, flags);
	else
	{
		if (flags->width > 0)
		{
			if (flags->zero == -1 && flags->minus == -1)
				flags->written += ft_print_blank(flags->width - len - 2, 0);
			flags->written += write(1, "0x", 2);
			if (flags->zero == 1)
				flags->written += ft_print_blank(flags->width - len - 2, 1);
			flags->written += write(1, str, ft_strlen(str));
			if (flags->zero == -1 && flags->minus == 1)
				flags->written += ft_print_blank(flags->width - len - 2, 0);
		}
		else
			ft_print_normal(str, len, flags);
	}
	free(str);
}
