/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:45:05 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/17 10:54:00 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	simple_execute(t_fresh *fresh, t_command *command)
{
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
		write_pipe_execute(fresh, command, pid, &fd);
	if (command->read_from_pipe && command->write_to_pipe)
		write_read_pipe_execute(fresh, command, pid, &fd);
	if (command->read_from_pipe && !command->write_to_pipe)
	{
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		read_pipe_execute(fresh, command, pid, &fd);
		waits(fresh, fresh->waits);
		fresh->waits = 0;
	}
}

void	execute_all(t_fresh *fresh, t_command *command, int *fd, int *pid)
{
	int	i;

	i = 0;
	ft_replace_exit_status(fresh, command);
	if (command->write_to_pipe)
		pipe(fd);
	setup_files(fresh, command, &i);
	if (fresh->last_in != NULL)
	{
		if (!setup_last_in(fresh))
			return ;
	}
	fresh->fd_out = dup(1);
	if (fresh->last_out != NULL)
		dup2(fresh->last_out->fd, 1);
	command_execute(fresh, command, pid, fd);
	close_files(fresh);
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
	fd = malloc(sizeof(int) * 2);
	while (list_elem)
	{
		command = (t_command *)list_elem->content;
		execute_all(fresh, command, fd, &pid);
		list_elem = list_elem->next;
	}
	free(fd);
}
