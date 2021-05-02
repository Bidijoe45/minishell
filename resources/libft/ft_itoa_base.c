/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:42:00 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/22 15:06:57 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chardup(char c)
{
	char *str;

	if (!(str = malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = ft_strdup(str);
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

void	ft_add_numbers(unsigned long nbr, char **str, int len, char *base)
{
	char	*tmp;

	if (nbr >= len)
		ft_add_numbers(nbr / len, str, len, base);
	tmp = *str;
	*str = ft_strjoin_char(*str, base[nbr % len]);
	free(tmp);
}

char	*ft_itoa_base(unsigned long nbr, char *base, int len)
{
	char	*str;

	str = ft_strdup("");
	ft_add_numbers(nbr, &str, len, base);
	return (str);
}
