/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:54:43 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/04 16:48:16 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_nbr(int nbr, t_flags *flags)
{
	long lnb;
	char c;

	lnb = nbr;
	if (lnb < 0)
	{
		lnb = -lnb;
		write(1, "-", 1);
		(flags->written)++;
	}
	if (lnb > 9)
	{
		ft_print_nbr(lnb / 10, flags);
		ft_print_nbr(lnb % 10, flags);
	}
	else
	{
		c = lnb + '0';
		write(1, &c, 1);
		(flags->written)++;
	}
}

int		ft_print_extra(int len, int precision, int width, int is_negative)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	precision = len > precision ? width : precision;
	width = width > precision ? width : precision;
	while (i < (width - precision))
	{
		i += write(1, " ", 1);
		ret++;
	}
	if (is_negative)
	{
		ret += write(1, "-", 1);
	}
	while (i < precision - len)
	{
		i += write(1, "0", 1);
		ret++;
	}
	return (ret);
}

void	ft_print_int(int nbr, t_flags *flags)
{
	int len;
	int is_null;
	int	is_negative;

	if (flags->precision <= 0 && nbr == 0)
		is_null = 1;
	if (nbr < 0)
	{
		is_negative = 1;
		flags->width += -1;
		nbr = -nbr;
	}
	len = is_null == -1 ? 0 : ft_get_length(nbr);
	flags->written +=
		ft_print_extra(len, flags->precision, flags->width, is_negative);
	if (is_null != -1)
		ft_print_nbr(nbr, flags);
}
