/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:48:04 by apavel            #+#    #+#             */
/*   Updated: 2020/03/02 15:57:13 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_display_width(t_flags *flags)
{
	int		i;
	char	empty_char;

	empty_char = (flags->f_zero == 1) ? '0' : ' ';
	i = 0;
	if (flags->f_width == 1)
		while (i++ < flags->n_width - 1)
			flags->printed += write(1, &empty_char, 1);
}

int				ft_display_c(t_flags *flags)
{
	int	c;

	c = va_arg(flags->args, int);
	if (flags->f_minus == 1)
	{
		flags->printed += write(1, &c, 1);
		ft_display_width(flags);
	}
	else
	{
		ft_display_width(flags);
		flags->printed += write(1, &c, 1);
	}
	return (flags->printed);
}
