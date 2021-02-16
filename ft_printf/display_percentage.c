/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_percentage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:16:50 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 12:25:38 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_display_percentage(t_flags *flags)
{
	int		i;
	char	empty_char;

	i = 0;
	empty_char = (flags->f_zero == 1) ? '0' : ' ';
	if (flags->f_minus == 1)
	{
		flags->printed += write(1, "%", 1);
		while (i++ < (flags->n_width - 1))
			flags->printed += write(1, &empty_char, 1);
	}
	else if (flags->f_width == 1)
	{
		while (i++ < (flags->n_width - 1))
			flags->printed += write(1, &empty_char, 1);
		flags->printed += write(1, "%", 1);
	}
	else
		flags->printed += write(1, "%", 1);
}
