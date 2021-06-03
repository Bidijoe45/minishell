/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:36:47 by alvrodri          #+#    #+#             */
/*   Updated: 2021/06/03 12:01:00 by alvrodri         ###   ########.fr       */
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
	{
		close((*fd)[0]);
		if (fresh->last_out != NULL)
		{
			dup2(fresh->last_out->fd, 1);
			close(fresh->last_out->fd);	
		}
		else
		{
			dup2((*fd)[1], 1);
			close((*fd)[1]);
		}
		if (ft_is_builtin(fresh, command))
			ft_execute_builtin(command, fresh);
		else
			ft_exec_bin(fresh, command, 1);
		exit(0);
	}
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
		close((*fd)[0]);
		dup2(fresh->last_fd, 0);
		close(fresh->last_fd);
		dup2((*fd)[1], 1);
		close((*fd)[1]);
		if (ft_is_builtin(fresh, command))
			ft_execute_builtin(command, fresh);
		else
			ft_exec_bin(fresh, command, 1);
		exit(0);
	}
	else
	{
		close((*fd)[1]);
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
		signal(SIGINT, global_sigquit);
		signal(SIGQUIT, global_sigquit);
		dup2(fresh->last_fd, 0);
		close(fresh->last_fd);
		if (ft_is_builtin(fresh, command))
			ft_execute_builtin(command, fresh);
		else
			ft_exec_bin(fresh, command, 1);
		exit(0);
	}
	else
	{
		close(fresh->last_fd);
		fresh->waits++;
	}
}
