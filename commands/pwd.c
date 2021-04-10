/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/04/10 11:31:52 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

int    ft_pwd(t_command *command, t_fresh *fresh)
{
	char *cwd;
	
	if (command->args[0])
	{
		if (command->args[0][0] == '-')
		{
			printf("pwd: %s: invalid option\n", command->args[0]);
			return (1);
		}
	}
	if (command->args[0])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
