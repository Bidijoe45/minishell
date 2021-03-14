/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/03/14 12:34:38 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "../print/print.h"
#include "command.h"

int	ft_env(t_fresh *fresh, t_command *command)
{
	t_list		*elem;
	t_variable	*var;

	if (!fresh->env)
		return (0);
	if (command->arg != NULL && command->arg[0] != '\0')
	{
		printf("\033%s%s\033%s%s\n", RED, "Error: ", RESET, "Options not supported.");
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
	return (1);
}
