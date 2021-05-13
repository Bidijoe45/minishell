/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:36:47 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 11:25:13 by alvrodri         ###   ########.fr       */
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
		dup2((*fd)[1], 1);
		ft_exec_bin(fresh, command, 1);
		exit(0);
	}
	else
	{
		close((*fd)[1]);
		fresh->last_fd = dup((*fd)[0]);
		close((*fd)[0]);
		fresh->waits++;
		//		wait(NULL);
	}
}

void	write_read_pipe_execute(t_fresh *fresh, t_command *command, int *pid,
		int *fd[2])
{
	*pid = fork();
	if (!(*pid))
	{
		dup2(fresh->last_fd, 0);
		dup2((*fd)[1], 1);
		close((*fd)[1]);
		ft_exec_bin(fresh, command, 1);
		exit(0);
	}
	else
	{
		close((*fd)[1]);
		fresh->last_fd = dup((*fd)[0]);
		close((*fd)[0]);
		fresh->waits++;
//		wait(NULL);
	}
}

void	read_pipe_execute(t_fresh *fresh, t_command *command, int *pid,
		int *fd[2])
{
	*pid = fork();
	if (!(*pid))
	{
		close((*fd)[0]);
		dup2(fresh->last_fd, 0);
		ft_exec_bin(fresh, command, 1);
		exit(0);
	}
	else
	{
		close((*fd)[1]);
		close((*fd)[0]);
		close(fresh->last_fd);
		fresh->waits++;
//		wait(NULL);
	}
}
