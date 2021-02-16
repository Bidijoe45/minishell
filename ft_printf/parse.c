/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:11:26 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 15:32:29 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*g_flags = "cspdiuxX";

void	ft_parse_flags(t_flags *flags, const char *format)
{
	int i;

	i = 0;
	while (format[i] == '-' || format[i] == '0')
	{
		if (format[i] == '-')
			flags->f_minus = 1;
		if (format[i] == '0' && flags->f_minus == 0)
			flags->f_zero = 1;
		i++;
	}
}

void	ft_parse_precision(t_flags *flags, const char *format)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (format[i] == '-' || format[i] == '0')
		i++;
	while (!ft_strchr(g_flags, format[i]) && format[i] != '.')
		i++;
	if (format[i] == '.')
	{
		flags->f_zero = 0;
		flags->f_precision = 1;
		i++;
		if (format[i] == '*')
		{
			flags->n_precision = va_arg(flags->args, int);
			return ;
		}
		while (format[i] >= '0' && format[i] <= '9')
			num = num * 10 + format[i++] - '0';
		flags->n_precision = num;
	}
}

int		ft_detect_type_and_display(t_flags *flags, const char *format)
{
	int i;

	i = 0;
	while (!ft_strchr(g_flags, format[i]) &&
			format[i] != '\0' && format[i] != '%')
		i++;
	if (format[i] == '%')
		ft_display_percentage(flags);
	else if (format[i] == '\0')
		return (0);
	else
	{
		flags->type = format[i];
		ft_display(flags, format[i]);
	}
	return (i);
}

int		ft_parse(t_flags *flags, va_list args, const char *format)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	ft_start_flags(flags, args);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			ft_restart_flags(flags);
			ft_parse_flags(flags, &format[i]);
			ft_parse_width(flags, &format[i]);
			ft_parse_precision(flags, &format[i]);
			i = i + ft_detect_type_and_display(flags, &format[i]);
			ret += flags->printed;
		}
		else
			ret += write(1, &format[i], 1);
		i++;
	}
	return (ret);
}
