/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:47:33 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/10 14:50:12 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	ft_free_commands_files(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->files[i])
	{
		free(cmd->files[i]->file_name);
		free(cmd->files[i]);
		i++;
	}
}

void	ft_free_commands_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
}

void	ft_free_commands(t_fresh *fresh)
{
	t_command	*cmd;
	t_list		*list_elem;

	list_elem = fresh->commands;
	while (list_elem)
	{
		cmd = (t_command *)list_elem->content;
		free(cmd->cmd);
		if (cmd->files)
			ft_free_commands_files(cmd);
		free(cmd->files);
		if (cmd->args)
			ft_free_commands_args(cmd);
		free(cmd->args);
		free(cmd);
		free(list_elem);
		list_elem = list_elem->next;
	}
	fresh->commands = NULL;
}
