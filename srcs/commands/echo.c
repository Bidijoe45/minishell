/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:13:11 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/11 11:40:07 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"

static	void	set_trail(char **args, int *trail)
{
	int	i;
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

void	echo_aux_1(t_command *command, t_echo *echo)
{
	echo->i = 0;
	echo->print = 0;
	if (!echo->already && command->args[echo->j][0]
		== '-' && command->args[echo->j][1] == 'n')
	{
		echo->i++;
		while (command->args[echo->j][echo->i] == 'n')
			echo->i++;
		if (command->args[echo->j][echo->i] != ' '
		&& command->args[echo->j][echo->i] != '\0')
			echo->print = 1;
	}
	else
	{
		echo->already = 1;
		echo->print = 1;
	}
	if (echo->print)
	{
		write(1, command->args[echo->j], ft_strlen(command->args[echo->j]));
		if (command->args[echo->j + 1])
			write(1, " ", 1);
	}
	echo->j++;
}

int	ft_echo(t_command *command, t_fresh *fresh)
{
	t_echo	echo;

	(void)fresh;
	echo.trail = 1;
	if (*command->args)
		set_trail(command->args, &echo.trail);
	if (echo.trail)
		echo.i = 0;
	else
		echo.i = 1;
	echo.print = 1;
	echo.j = 0;
	echo.already = 0;
	while (command->args[echo.j])
	{
		echo_aux_1(command, &echo);
	}
	if (echo.trail)
		write(1, "\n", 1);
	return (0);
}
