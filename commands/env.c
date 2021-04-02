/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/04/02 17:30:43 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "../print/print.h"
#include "command.h"

int	ft_env(t_command *command, t_fresh *fresh)
{
	t_list		*elem;
	t_variable	*var;

	if (!fresh->env)
		return (1);
	if (*command->args)
	{
		printf("env: options not supported\n");
		return (1);
	}
	elem = fresh->env;
	while (elem)
	{
		var = (t_variable *)elem->content;
		if (var->key && var->value)
			printf("%s=%s\n", var->key, var->value);
		elem = elem->next;
	}
	return (0);
}
