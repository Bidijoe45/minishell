/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:28:49 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 14:46:50 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_display(t_flags *flags, char type)
{
	if (type == 'c')
		ft_display_c(flags);
	else if (type == 's')
		ft_display_s(flags);
	else if (type == 'p')
		ft_display_p(flags);
	else if (type == 'd' || type == 'i')
		ft_display_int(flags);
	else if (type == 'u')
		ft_display_u(flags);
	else if (type == 'x')
		ft_display_x(flags);
	else if (type == 'X')
		ft_display_x(flags);
	return (0);
}
