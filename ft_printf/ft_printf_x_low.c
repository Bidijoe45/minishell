/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_low.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 10:15:55 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/27 12:48:59 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_x_precision(char *str, t_flags *flags)
{
	char	*tmp;
	int		len;

	tmp = str;
	len = ft_strlen(str);
	if (flags->width > 0 && flags->minus != 1)
		flags->written +=
			ft_print_blank(flags->width - flags->precision, 0);
	if (flags->precision > len)
		flags->written +=
			ft_print_blank(flags->precision - len, 1);
	if (flags->precision != 0)
	{
		ft_putstr_fd(str, 1);
		flags->written += len;
	}
	if (flags->width > 0 && flags->minus == 1)
		flags->written +=
			ft_print_blank(flags->width - flags->precision, 0);
	free(tmp);
}

void	ft_print_x_low(unsigned int nbr, t_flags *flags)
{
	char *str;

	str = ft_itoa_base(nbr, "0123456789abcdef", 16);
	if (flags->precision == 0)
	{
		ft_print_blank(flags->width, flags->zero);
		if (flags->width > 0)
			(flags->written) += flags->width;
		return ;
	}
	if (flags->precision != -1 && ft_strlen(str) < flags->precision)
		return (ft_print_x_precision(str, flags));
	if (flags->minus == -1 && flags->width > 0)
		flags->written +=
			ft_print_blank(flags->width - ft_strlen(str), flags->zero);
	ft_putstr_fd(str, 1);
	flags->written += ft_strlen(str);
	if (flags->minus == 1 && flags->width > 0)
		flags->written +=
			ft_print_blank(flags->width - ft_strlen(str), flags->zero);
	free(str);
}
