/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/12/18 12:25:39 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void    ft_env(t_fresh *fresh)
{
	t_list		*elem;
	t_variable	*var;

	if (!fresh->env)
		return ;
	elem = fresh->env;
	while (elem)
	{
		var = (t_variable *)elem->content;
		if (var->key && var->value)
			ft_printf("%s=%s\n", var->key, var->value);
		else
			ft_printf("empty var\n");
		elem = elem->next;
	}
}