/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:51:34 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/10 14:58:57 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

void	setup_files(t_fresh *fresh, t_command *command, int *i)
{
	while (command->files[*i])
	{
		if (command->files[*i]->type == IN)
			fresh->last_in = command->files[*i];
		else
		{
			if (fresh->last_out)
				close(fresh->last_out->fd);
			fresh->last_out = command->files[*i];
			if (fresh->last_out->type == OUT)
				fresh->last_out->fd = open(fresh->last_out->file_name,
						O_RDWR | O_TRUNC | O_CREAT, 0700);
			else if (fresh->last_out->type == APPEND)
				fresh->last_out->fd = open(fresh->last_out->file_name,
						O_RDWR | O_APPEND | O_CREAT, 0700);
		}
		(*i)++;
	}
}

void	setup_last_in(t_fresh *fresh)
{
	fresh->last_in->fd = open(fresh->last_in->file_name, O_RDONLY);
	if (fresh->last_in->fd == -1)
	{
		fresh->cmd_return = 1;
		printf("%s: No such file or directory\n", fresh->last_in->file_name);
		return ;
	}
	fresh->fd_in = dup(0);
	dup2(fresh->last_in->fd, 0);
}

void	close_files(t_fresh *fresh)
{
	if (fresh->last_in != NULL)
	{
		close(fresh->last_in->fd);
		dup2(fresh->fd_in, 0);
	}
	if (fresh->last_out != NULL)
	{
		close(fresh->last_out->fd);
		dup2(fresh->fd_out, 1);
	}
}