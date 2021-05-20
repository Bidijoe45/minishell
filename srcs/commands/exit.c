/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/05/20 13:39:58 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"

int	check_errors(t_fresh *fresh, t_command *command, int *i)
{
	*i = 0;
	while (command->args[*i])
		*i = *i + 1;
	if (*i == 0)
		exit(fresh->cmd_return);
	if (*i > 1)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	*i = 0;
	return (0);
}

int	ft_exit(t_command *command, t_fresh *fresh)
{
	int	i;
	int	code;

	if (check_errors(fresh, command, &i))
		return (1);
	while (command->args[0][i] == ' ')
		i++;
	if (command->args[0][i] == '-' || command->args[0][i] == '+')
		i++;
	while (command->args[0][i])
	{
		if (!ft_isdigit(command->args[0][i]))
		{
			printf("exit: %s: numeric argument required\n", command->args[0]);
			exit(255);
		}
		i++;
	}
	code = ft_atoi(command->args[0]);
	if (code < 0)
		code = 256 + code;
	else if (code > 255)
		code = code - 256;
	exit(code);
	return (code);
}
