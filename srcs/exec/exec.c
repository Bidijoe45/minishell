/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:45:05 by alvrodri          #+#    #+#             */
/*   Updated: 2021/06/01 13:30:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	simple_execute(t_fresh *fresh, t_command *command)
{
	if (fresh->last_out != NULL)
		dup2(fresh->last_out->fd, 1);
	if (ft_is_builtin(fresh, command))
		ft_execute_builtin(command, fresh);
	else
		ft_exec_bin(fresh, command, 0);
}

void	waits(t_fresh *fresh, int n)
{
	int	status;
	int	i;

	i = -1;
	while (++i < n)
		wait(&status);
	fresh->pid = status >> 8;
}

void	command_execute(t_fresh *fresh, t_command *command, int *pid, int *fd)
{
	if (!command->write_to_pipe && !command->read_from_pipe)
	{
		simple_execute(fresh, command);
		waits(fresh, fresh->waits);
		fresh->waits = 0;
	}
	if (command->write_to_pipe && !command->read_from_pipe)
	{
		write_pipe_execute(fresh, command, pid, &fd);
	}
	if (command->read_from_pipe && command->write_to_pipe)
		write_read_pipe_execute(fresh, command, pid, &fd);
	if (command->read_from_pipe && !command->write_to_pipe)
	{
		read_pipe_execute(fresh, command, pid, &fd);
		waits(fresh, fresh->waits);
		fresh->waits = 0;
	}
}

int	execute_all(t_fresh *fresh, t_command *command, int *fd, int *pid)
{
	int	i;
	int	code;

	i = 0;
	ft_replace_exit_status(fresh, command);
	replace_vars_quotes(fresh, command);
	if (command->write_to_pipe)
		pipe(fd);
	code = setup_files(fresh, command, &i);
	if (code)
	{
		fresh->cmd_return = 1;
		return (1);
	}
	if (fresh->last_in != NULL)
	{
		if (!setup_last_in(fresh))
			return (1);
	}
	fresh->fd_out = dup(1);
	command_execute(fresh, command, pid, fd);
	close_files(fresh);
	return (0);
}

void	ft_execute_commands(t_fresh *fresh)
{
	int			pid;
	int			*fd;	
	t_list		*list_elem;
	t_command	*p_command;
	t_command	*command;

	fresh->last_in = NULL;
	fresh->last_out = NULL;
	fresh->waits = 0;
	p_command = NULL;
	list_elem = fresh->commands;
	fd = ft_malloc(sizeof(int) * 2);
	while (list_elem)
	{
		command = (t_command *)list_elem->content;
		if (execute_all(fresh, command, fd, &pid))
		{
			free(fd);
			return ;
		}
		if (command->write_to_pipe && fresh->last_out != NULL)
			((t_command *)list_elem->next->content)->redir = 1;
		list_elem = list_elem->next;
	}
	free(fd);
}
