/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:24:47 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/27 15:55:27 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_print_str(va_list list, t_flags *flags)
{
	char	*str;
	char	*tmp;
	int		len;

	str = va_arg(list, char *);
	if (str == NULL)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (flags->precision > -1)
	{
		tmp = str;
		str = ft_substr(tmp, 0, flags->precision);
		free(tmp);
	}
	len = ft_strlen(str);
	if (flags->width > 0 && flags->minus == -1)
		flags->written += ft_print_blank(flags->width - len, flags->zero);
	flags->written += write(1, str, len);
	if (flags->width > 0 && flags->minus == 1)
		flags->written += ft_print_blank(flags->width - len, flags->zero);
	free(str);
}
