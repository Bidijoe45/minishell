/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:11:42 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 12:17:56 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_display_width(t_flags *flags, char *num)
{
	int		i;
	char	empty_char;
	int		len;

	empty_char = (flags->f_zero && flags->f_precision == 0) ? '0' : ' ';
	i = 0;
	if (flags->f_width == 1 && flags->n_width > ft_strlen(num))
	{
		if (flags->f_precision == 1 && flags->n_precision > ft_strlen(num))
		{
			i = (num[0] == '-') ? 1 : 0;
			while (i++ < (len = (flags->n_width - ft_strlen(num) -
					(flags->n_precision - ft_strlen(num)))))
				flags->printed += write(1, &empty_char, 1);
		}
		else
		{
			if (flags->f_precision == 1 && flags->n_precision == 0)
				while (i++ < flags->n_width)
					flags->printed += write(1, &empty_char, 1);
			else
				while (i++ < (flags->n_width - ft_strlen(num)))
					flags->printed += write(1, &empty_char, 1);
		}
	}
}

static void		ft_display_precision(t_flags *flags, char *num)
{
	int		i;

	if (flags->n_precision > ft_strlen(num))
	{
		if (num[0] == '-')
			flags->printed += write(1, "-", 1);
		i = 0;
		if (num[0] == '-')
		{
			num++;
			while (i++ < flags->n_precision - (int)ft_strlen(num))
				flags->printed += write(1, "0", 1);
		}
		else
		{
			while (i++ < flags->n_precision - ft_strlen(num))
				flags->printed += write(1, "0", 1);
		}
	}
}

static void		ft_display_int_inverse(t_flags *flags, char *num)
{
	ft_display_precision(flags, num);
	if (num[0] == '-' && (flags->f_zero == 1
		|| flags->n_precision > ft_strlen(num)))
	{
		num++;
		flags->printed += write(1, num, ft_strlen(num));
		num--;
	}
	else
	{
		if (flags->f_precision == 1 && flags->n_precision == 0)
		{
			ft_display_width(flags, num);
			return ;
		}
		flags->printed += write(1, num, ft_strlen(num));
	}
	ft_display_width(flags, num);
}

static void		ft_display_num(char *num, t_flags *flags)
{
	if (flags->f_precision == 1 && flags->n_precision == 0)
	{
		ft_display_width(flags, num);
		return ;
	}
	if (num[0] == '-' && flags->f_precision == 1 && flags->n_precision == 0)
		return ;
	if (num[0] == '-' && flags->f_zero == 1)
		flags->printed += write(1, "-", 1);
	ft_display_width(flags, num);
	ft_display_precision(flags, num);
	if (num[0] == '-' && (flags->f_zero == 1
		|| flags->n_precision > ft_strlen(num)))
	{
		num++;
		flags->printed += write(1, num, ft_strlen(num));
		--num;
	}
	else
	{
		flags->printed += write(1, num, ft_strlen(num));
	}
}

int				ft_display_int(t_flags *flags)
{
	char	*num;

	num = ft_itoa(va_arg(flags->args, int));
	if (flags->f_minus == 1)
		ft_display_int_inverse(flags, num);
	else
		ft_display_num(num, flags);
	free(num);
	return (flags->printed);
}
