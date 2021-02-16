/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:28:54 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 14:55:48 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	ft_count_digits(unsigned long n)
{
	unsigned long digits;

	digits = 1;
	while (n / 16 > 0)
	{
		digits++;
		n = n / 16;
	}
	return (digits);
}

char					*ft_itox(unsigned long n, char type)
{
	char	*str;
	int		i;
	int		digits;

	digits = ft_count_digits(n);
	if (!(str = malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	i = digits - 1;
	str[digits] = '\0';
	str[0] = '0';
	while (n > 0)
	{
		if (n % 16 > 9)
		{
			if (type == 'x' || type == 'p')
				str[i] = (n % 16) + 87;
			if (type == 'X')
				str[i] = (n % 16) + 55;
		}
		else
			str[i] = (n % 16) + '0';
		n = n / 16;
		i--;
	}
	return (str);
}
