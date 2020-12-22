/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/12/21 12:18:08 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void		ft_export_inline(t_fresh *fresh, char *cmd)
{
	char **split_cmd;

	split_cmd = ft_split(cmd, '=');
	variable_set(fresh->env, split_cmd[0], split_cmd[1]);
	variable_set(fresh->local_vars, split_cmd[0], split_cmd[1]);
	free(split_cmd);
}

void		ft_export(t_fresh *fresh)
{
	char **split_cmd;
	t_variable *var;
	
	split_cmd = ft_split(fresh->line, ' ');
	if (ft_strchr(split_cmd[1], '='))
	{
		ft_export_inline(fresh, split_cmd[1]);
	}
	else
	{
		var = variable_get(fresh->local_vars, split_cmd[1]);
		variable_set(fresh->env, var->key, var->value);
	}
	free(split_cmd[0]);
	free(split_cmd[1]);
	free(split_cmd);
}