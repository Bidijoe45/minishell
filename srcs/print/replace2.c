/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:09:14 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/29 15:16:54 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/libft/libft.h"
#include "../../includes/fresh.h"

static	char	*ft_replace_aux(t_replace *rpl, char *str, char *key,
	char *word)
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

char	*ft_replace2(char *str, char *key, char *word, int n)
{
	t_replace	rpl;

	rpl.i = -1;
	rpl.j = 0;
	if (!str || !key || !word)
		return (NULL);
	if (!ft_strnstr(str, key, ft_strlen(str)))
		return (ft_strdup(str));
	rpl.alvaro = ft_strdup(str);
	while (rpl.alvaro[++rpl.i])
	{
		if (rpl.alvaro[rpl.i] == '\\')
			rpl.i++;
		else if (rpl.alvaro[rpl.i] == key[0])
		{
			if (!ft_strncmp(&rpl.alvaro[rpl.i], key, ft_strlen(key))
				&& is_between_quotes2(rpl.alvaro, rpl.i) != 1)
			{
				if (n != 0 && rpl.j == n)
					break ;
				rpl.alvaro = ft_replace_aux(&rpl, rpl.alvaro, key, word);
			}
		}
	}
	return (rpl.alvaro);
}
