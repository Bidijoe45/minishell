/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:59:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/20 13:46:08 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	replace_vars_quotes_aux(t_fresh *fresh, t_command *command)
{
	char	*tmp;
	int		i;

	i = -1;
	while (command->files[++i])
	{
		tmp = command->files[i]->file_name;
		command->files[i]->file_name
			= ft_replace_vars(fresh, command->files[i]->file_name);
		free(tmp);
		tmp = command->files[i]->file_name;
		command->files[i]->file_name = trim_q_ftw(tmp);
		free(tmp);
	}
}

void	replace_vars_quotes(t_fresh *fresh, t_command *command)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = command->cmd;
	command->cmd = ft_replace_vars(fresh, command->cmd);
	free(tmp);
	tmp = command->cmd;
	command->cmd = trim_q_ftw(tmp);
	free(tmp);
	while (command->args[++i])
	{
		tmp = command->args[i];
		command->args[i] = ft_replace_vars(fresh, command->args[i]);
		free(tmp);
		tmp = command->args[i];
		command->args[i] = trim_q_ftw(tmp);
		free(tmp);
	}
	replace_vars_quotes_aux(fresh, command);
}
