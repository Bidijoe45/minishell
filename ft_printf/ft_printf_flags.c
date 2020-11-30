/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:10:18 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/22 15:35:23 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_check_first(const char *str, t_flags *flags, va_list args, int i)
{
	int j;

	j = 0;
	while (str[i] == '0')
	{
		flags->zero = 1;
		i++;
		j++;
	}
	if (str[i] == '-')
	{
		flags->minus = 1;
		i++;
		j++;
	}
	while (str[i] == '0')
	{
		flags->zero = 1;
		i++;
		j++;
	}
	return (j);
}

int	ft_check_second(const char *str, t_flags *flags, va_list args, int i)
{
	int j;
	int diff;

	j = 0;
	if (str[i] == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->width = -(flags->width);
			flags->minus = 1;
		}
		i++;
		j++;
	}
	else
	{
		diff = i;
		flags->width = ft_get_nbr(str, &i);
		j = i - diff;
	}
	return (j);
}

int	ft_enable_flags(const char *str, t_flags *flags, va_list args)
{
	int i;

	i = 0;
	i += ft_check_first(str, flags, args, i);
	i += ft_check_second(str, flags, args, i);
	if (str[i] == '.')
	{
		i++;
		if (!ft_isdigit(str[i]) && str[i] != '*' && !ft_isalpha(str[i]))
			return (-1);
		if (str[i] == '*')
		{
			flags->precision = va_arg(args, int);
			i++;
		}
		else
			flags->precision = ft_get_nbr(str, &i);
	}
	if (!ft_isalpha(str[i]) && str[i] != '%')
		return (1);
	if (flags->precision < 0)
		flags->precision = -1;
	ft_print_specific(str[i], args, flags);
	return (i + 2);
}
