/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/04/03 11:39:34 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

int	ft_exit(t_command *command, t_fresh *fresh)
{
	int	i;
	int	code;

	i = 0;
	while (command->args[i])
		i++;
	if (i == 0)
		return (0);
	if (i > 1)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (command->args[0][i] == ' ')
		i++;
	if (command->args[0][i] == '-' || command->args[0][i] == '+')
		i++;
	while (command->args[0][i])
	{
		if (!ft_isdigit(command->args[0][i]))
		{
			printf("exit: %s: numeric argument required\n", command->args[0]);
			return (1);
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
