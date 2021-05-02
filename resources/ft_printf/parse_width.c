/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:09:32 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 15:35:06 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *g_flags = "cspdiuxX";

void	ft_parse_star(t_flags *flags, int num)
{
	flags->f_width = 1;
	num = va_arg(flags->args, int);
	if (num < 0)
	{
		flags->f_minus = 1;
		flags->f_zero = 0;
		flags->n_width = num * -1;
	}
	else
		flags->n_width = num;
}

void	ft_parse_width(t_flags *flags, const char *format)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (format[i] == '-' || format[i] == '0')
		i++;
	while (format[i] && !ft_strchr(g_flags, format[i]) &&
		format[i] != '.' && format[i] != '%')
	{
		if (format[i] == '*')
		{
			ft_parse_star(flags, num);
			return ;
		}
		else if (format[i] >= '0' && format[i] <= '9')
		{
			flags->f_width = 1;
			num = num * 10 + (format[i] - '0');
		}
		i++;
	}
	flags->n_width = num;
}
