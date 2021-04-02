/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:13:11 by alvrodri          #+#    #+#             */
/*   Updated: 2021/04/02 17:48:23 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

static	void	set_trail(char **args, int *trail)
{
	int i;

	i = 0;
	if (args[0][0] == '-' && args[0][1] == 'n')
	{
		i++;
		while (args[0][i] == 'n')
			i++;
		*trail = 0;
		if (args[0][i] != ' ' && args[0][i] != '\0')
			*trail = 1;
	}
}

int	ft_echo(t_command *command, t_fresh *fresh)
{
	int	trail;
	int	i;

	trail = 1;
	if (command->args)
		set_trail(command->args, &trail);
	if (trail)
		i = 0;
	else
		i = 1;
	while (command->args[i])
	{
		write(1, command->args[i], ft_strlen(command->args[i]));
		if (command->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (trail)
		write(1, "\n", 1);
	return (0);
}
