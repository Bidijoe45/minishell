/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:39:21 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/25 11:39:39 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

char *ft_get_var(t_fresh fresh, char *name)
{
	int	len;
	int i;

	i = 0;
	len = ft_strlen(name);
	while (fresh.env[i])
	{
		if (!ft_strncmp(fresh.env[i], name, len))
			return ft_substr(fresh.env[i], len + 1, ft_strlen(fresh.env[i]) - len - 1);
		i++;
	}
	return (NULL);
}