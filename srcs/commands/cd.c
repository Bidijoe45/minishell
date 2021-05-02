/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/05/02 13:02:58 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"

int	ft_cd(t_command *command, t_fresh *fresh)
{
	char	*path;
	char	*old;
	int		code;
	int		i;

	i = 0;
	while (command->args[i])
		i++;
	if (i > 1)
	{
		printf("cd: too many arguments\n");
		return (-1);
	}
	if (i == 0)
	{
		if (variable_get(fresh->env, "HOME") == NULL)
			return (0);
		path = variable_get(fresh->env, "HOME")->value;
	}
	else
		path = command->args[0];
	old = getcwd(NULL, 0);
	code = chdir(path);
	if (code == -1)
	{
		printf("cd: %s\n", strerror(errno));
		return (-1);
	}
	// getcwd -> *dup* luego se borra maybe? (leak probs)
	if (variable_get(fresh->env, "OLDPWD") == NULL)
		variable_set(&fresh->env, "OLDPWD", old);
	else
		variable_mod(fresh->env, "OLDPWD", old);
	variable_mod(fresh->env, "PWD", getcwd(NULL, 0));
	return (0);
}
