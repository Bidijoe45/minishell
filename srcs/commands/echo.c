/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:13:11 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/02 13:05:33 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"

static	void	set_trail(char **args, int *trail)
{
	int i;
	int	j;
	int	already;

	j = 0;
	already = 0;
	while (args[j] && !already)
	{
		i = 0;
		if (args[j][0] == '-' && args[j][1] == 'n')
		{
			i++;
			while (args[j][i] == 'n')
				i++;
			*trail = 0;
			if (args[j][i] != ' ' && args[j][i] != '\0')
				*trail = 1;
		}
		else
			already = 1;
		j++;
	}
}

int	ft_echo(t_command *command, t_fresh *fresh)
{
	int	trail;
	int	print;
	int already;
	int	i;
	int	j;

	trail = 1;
	if (*command->args)
		set_trail(command->args, &trail);
	if (trail)
		i = 0;
	else
		i = 1;
	print = 1;
	j = 0;
	already = 0;
	while (command->args[j])
	{
		i = 0;
		print = 0;
		if (!already && command->args[j][0] == '-' && command->args[j][1] == 'n')
		{
			i++;
			while (command->args[j][i] == 'n')
				i++;
			if (command->args[j][i] != ' ' && command->args[j][i] != '\0')
				print = 1;
		}
		else
		{
			already = 1;
			print = 1;
		}
		if (print)
		{
			write(1, command->args[j], ft_strlen(command->args[j]));
			if (command->args[j + 1])
				write(1, " ", 1);
		}
		j++;
	}
	if (trail)
		write(1, "\n", 1);
	return (0);
}
