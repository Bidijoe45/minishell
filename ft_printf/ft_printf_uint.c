/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:17:58 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/20 15:04:32 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_unbr(unsigned int nbr, t_flags *flags)
{
	long lnb;
	char c;

	lnb = nbr;
	if (lnb > 9)
	{
		ft_print_unbr(lnb / 10, flags);
		ft_print_unbr(lnb % 10, flags);
	}
	else
	{
		c = lnb + '0';
		write(1, &c, 1);
		(flags->written)++;
	}
}

void	ft_print_uextra(unsigned int *nbr, int len, t_flags *flags)
{
	int i;

	i = 0;
	while (i < flags->width - len)
	{
		if (flags->zero == 1)
			write(1, flags->precision != -1 ? " " : "0", 1);
		else
			write(1, " ", 1);
		(flags->written)++;
		i++;
	}
}

void	ft_print_uwidth(t_flags *flags)
{
	int i;

	i = 0;
	while (i < flags->width - flags->precision)
	{
		write(1, " ", 1);
		(flags->written)++;
		i++;
	}
}

void	ft_print_uprec(unsigned int nbr, t_flags *flags)
{
	int i;

	if (flags->minus == -1)
		ft_print_uwidth(flags);
	i = 0;
	while (i < flags->precision - ft_get_length(nbr))
	{
		write(1, "0", 1);
		(flags->written)++;
		i++;
	}
	ft_print_unbr(nbr, flags);
	if (flags->minus == 1)
		ft_print_uwidth(flags);
}

void	ft_print_uint(unsigned int nbr, t_flags *flags)
{
	if (flags->precision == 0)
	{
		ft_print_blank(flags->width, flags->zero);
		if (flags->width > 0)
			(flags->written) += flags->width;
		return ;
	}
	if (flags->precision != -1 && ft_get_length(nbr) < flags->precision)
		ft_print_uprec(nbr, flags);
	else
	{
		if (flags->minus == 1)
		{
			ft_print_unbr(nbr, flags);
			ft_print_uextra(&nbr, ft_get_length(nbr), flags);
		}
		else
		{
			ft_print_uextra(&nbr, ft_get_length(nbr), flags);
			ft_print_unbr(nbr, flags);
		}
	}
}
