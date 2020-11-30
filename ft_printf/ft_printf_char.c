/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:55:46 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/27 15:50:59 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_char(char c, t_flags *flags)
{
	if (flags->width != -1 && flags->minus != 1)
		flags->written += ft_print_blank(flags->width - 1, flags->zero);
	flags->written += write(1, &c, 1);
	if (flags->width != 1 && flags->minus == 1)
		flags->written += ft_print_blank(flags->width - 1, flags->zero);
}
