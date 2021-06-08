/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:42:41 by apavel            #+#    #+#             */
/*   Updated: 2021/06/08 11:25:38 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	fork_write_pipe_execute(t_fresh *fresh, t_command *command, int *fd[2])
{
	close((*fd)[0]);
	if (fresh->last_out != NULL)
	{
		dup2(fresh->last_out->fd, 1);
		close(fresh->last_out->fd);
		close((*fd)[1]);
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

void	fork_write_read_pipe_execute(t_fresh *fresh, t_command *command,
	int *fd[2])
{
	close((*fd)[0]);
	if (fresh->last_out != NULL)
	{
		dup2(fresh->last_fd, 0);
		dup2(fresh->last_out->fd, 1);
		close(fresh->last_out->fd);
		close(fresh->last_fd);
	}
	else
	{
		dup2(fresh->last_fd, 0);
		close(fresh->last_fd);
		dup2((*fd)[1], 1);
	}
	close((*fd)[1]);
	if (ft_is_builtin(fresh, command))
		ft_execute_builtin(command, fresh);
	else
		ft_exec_bin(fresh, command, 1);
	exit(0);
}

void	fork_read_pipe_execute(t_fresh *fresh, t_command *command)
{
	signal(SIGINT, global_sigquit);
	signal(SIGQUIT, global_sigquit);
	if (fresh->last_out != NULL)
	{
		dup2(fresh->last_fd, 0);
		dup2(fresh->last_out->fd, 1);
		close(fresh->last_out->fd);
		close(fresh->last_fd);
	}
	else
	{
		dup2(fresh->last_fd, 0);
		close(fresh->last_fd);
	}
	if (ft_is_builtin(fresh, command))
		ft_execute_builtin(command, fresh);
	else
		ft_exec_bin(fresh, command, 1);
	exit(fresh->cmd_return);
}
