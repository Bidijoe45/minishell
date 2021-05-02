/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:49:25 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 14:38:13 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_start_flags(t_flags *flags, va_list args)
{
	flags->printed = 0;
	flags->f_minus = 0;
	flags->f_zero = 0;
	flags->f_width = 0;
	flags->n_width = 0;
	flags->f_precision = 0;
	flags->n_precision = 0;
	flags->type = 0;
	va_copy(flags->args, args);
}

void	ft_restart_flags(t_flags *flags)
{
	flags->printed = 0;
	flags->f_minus = 0;
	flags->f_zero = 0;
	flags->f_width = 0;
	flags->n_width = 0;
	flags->f_precision = 0;
	flags->n_precision = 0;
	flags->type = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	t_flags		flags;
	int			ret;

	va_start(args, format);
	i = 0;
	ret = 0;
	ret = ft_parse(&flags, args, format);
	return (ret);
}
