/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:45:49 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 12:23:51 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_display_width(t_flags *flags, char *dir)
{
	int	i;

	i = 0;
	if (flags->f_width == 1 && (ft_strlen(dir) + 2) < flags->n_width)
	{
		if (ft_strlen(dir) == 1 && flags->f_precision == 1
				&& flags->n_precision == 0)
			while (i++ < flags->n_width - 2)
				flags->printed += write(1, " ", 1);
		else if (ft_strlen(dir) == 1)
			while (i++ < flags->n_width - (ft_strlen(dir) + 2))
				flags->printed += write(1, " ", 1);
		else
			while (i++ < flags->n_width - (ft_strlen(dir) + 2))
				flags->printed += write(1, " ", 1);
	}
}

static void		ft_display_precision(t_flags *flags, char *dir)
{
	int i;

	i = 0;
	if (flags->f_precision == 1 && flags->n_precision > ft_strlen(dir))
	{
		while (i++ < flags->n_precision - ft_strlen(dir))
			flags->printed += write(1, "0", 1);
	}
}

void			ft_display_inverse(t_flags *flags, char *dir)
{
	flags->printed += write(1, "0x", 2);
	ft_display_precision(flags, dir);
	flags->printed += write(1, dir, ft_strlen(dir));
	ft_display_width(flags, dir);
}

int				ft_display_p(t_flags *flags)
{
	char			*dir;
	unsigned long	n;

	n = (unsigned long)va_arg(flags->args, void *);
	dir = ft_itox(n, flags->type);
	if (n == 0)
	{
		ft_display_width(flags, dir);
		flags->printed += write(1, "0x", 2);
		ft_display_precision(flags, dir);
		if (!(flags->f_precision == 1 && flags->n_precision == 0))
			flags->printed += write(1, dir, 1);
	}
	else if (flags->f_minus == 1)
		ft_display_inverse(flags, dir);
	else
	{
		ft_display_width(flags, dir);
		flags->printed += write(1, "0x", 2);
		ft_display_precision(flags, dir);
		flags->printed += write(1, dir, ft_strlen(dir));
	}
	free(dir);
	return (flags->printed);
}
