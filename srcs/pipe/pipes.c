/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:36:47 by alvrodri          #+#    #+#             */
/*   Updated: 2021/06/08 11:25:52 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	write_pipe_execute(t_fresh *fresh, t_command *command, int *pid,
		int *fd[2])
{
	*pid = fork();
	if (!(*pid))
		fork_write_pipe_execute(fresh, command, fd);
	else
	{
		close((*fd)[1]);
		fresh->last_fd = dup((*fd)[0]);
		close((*fd)[0]);
		fresh->waits++;
	}
}

void	write_read_pipe_execute(t_fresh *fresh, t_command *command, int *pid,
		int *fd[2])
{
	*pid = fork();
	if (!(*pid))
	{
		fork_write_read_pipe_execute(fresh, command, fd);
	}
	else
	{
		close((*fd)[1]);
		close(fresh->last_fd);
		if (command->redir != 1)
			fresh->last_fd = dup((*fd)[0]);
		close((*fd)[0]);
		fresh->waits++;
	}
}

void	read_pipe_execute(t_fresh *fresh, t_command *command, int *pid,
		int *fd[2])
{
	(void)fd;
	*pid = fork();
	if (!(*pid))
	{
		fork_read_pipe_execute(fresh, command);
	}
	else
	{
		fresh->pid = *pid;
		close(fresh->last_fd);
		fresh->waits++;
	}
}
