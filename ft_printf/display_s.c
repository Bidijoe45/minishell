/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:58:46 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 12:27:17 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_display_width(t_flags *flags, char *str)
{
	int		i;
	char	empty_char;

	empty_char = (flags->f_zero == 1) ? '0' : ' ';
	i = 0;
	if (flags->f_precision == 1 && flags->f_width == 1)
	{
		if (flags->n_precision < ft_strlen(str))
			while (i++ < flags->n_width - flags->n_precision)
				flags->printed += write(1, &empty_char, 1);
		else
		{
			if (flags->n_width > ft_strlen(str))
				while (i++ < flags->n_width - ft_strlen(str))
					flags->printed += write(1, &empty_char, 1);
		}
	}
	else if (flags->f_width == 1)
	{
		if (flags->n_width > ft_strlen(str))
			while (i++ < flags->n_width - ft_strlen(str))
				flags->printed += write(1, &empty_char, 1);
	}
}

int				ft_display_s(t_flags *flags)
{
	char *str;

	str = va_arg(flags->args, char *);
	if (str == NULL)
		str = "(null)";
	if (flags->f_minus == 1)
	{
		if (flags->f_precision == 1 && flags->n_precision < ft_strlen(str))
			flags->printed += write(1, str, flags->n_precision);
		else
			flags->printed += write(1, str, ft_strlen(str));
		ft_display_width(flags, str);
	}
	else
	{
		ft_display_width(flags, str);
		if (flags->f_precision == 1 && flags->n_precision < ft_strlen(str))
			flags->printed += write(1, str, flags->n_precision);
		else
			flags->printed += write(1, str, ft_strlen(str));
	}
	return (flags->printed);
}
