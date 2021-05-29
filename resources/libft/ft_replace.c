/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:09:33 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/22 18:09:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_aux(t_replace *rpl, char *str, char *key, char *word)
{
	char	*tmp;

	rpl->tmp = ft_substr(str, 0, &str[rpl->i] - str);
	rpl->tmp2 = ft_substr(&str[rpl->i + ft_strlen(key)], 0,
			ft_strlen(&str[rpl->i + ft_strlen(key)]));
	rpl->tmp3 = ft_strjoin(word, rpl->tmp2);
	tmp = str;
	str = ft_strjoin(rpl->tmp, rpl->tmp3);
	free(tmp);
	free(rpl->tmp);
	free(rpl->tmp2);
	free(rpl->tmp3);
	rpl->j++;
	rpl->i = -1;
	return (str);
}

char	*ft_replace(char *str, char *key, char *word, int n)
{
	t_replace	rpl;

	rpl.i = 0;
	rpl.j = 0;
	if (!str || !key || !word)
		return (NULL);
	if (!ft_strnstr(str, key, ft_strlen(str)))
		return (ft_strdup(str));
	rpl.tmp4 = ft_strdup(str);
	while (rpl.tmp4[rpl.i])
	{
		if (rpl.tmp4[rpl.i] == key[0])
		{
			if (!ft_strncmp(&rpl.tmp4[rpl.i], key, ft_strlen(key)))
			{
				if (n != 0 && rpl.j == n)
					break ;
				rpl.tmp4 = ft_replace_aux(&rpl, rpl.tmp4, key, word);
			}
		}
		rpl.i++;
	}
	return (rpl.tmp4);
}
