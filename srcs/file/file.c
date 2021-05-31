/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:51:34 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/31 09:52:06 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

int	setup_files(t_fresh *fresh, t_command *command, int *i)
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
			if (fresh->last_out->fd < 0)
			{
				printf("minishell: %s: %s\n", fresh->last_out->file_name,
					strerror(errno));
				return (1);
			}
		}
		(*i)++;
	}
	return (0);
}

int	setup_last_in(t_fresh *fresh)
{
	fresh->last_in->fd = open(fresh->last_in->file_name, O_RDONLY);
	if (fresh->last_in->fd == -1)
	{
		fresh->cmd_return = 1;
		printf("%s: No such file or directory\n", fresh->last_in->file_name);
		return (0);
	}
	fresh->fd_in = dup(0);
	dup2(fresh->last_in->fd, 0);
	return (1);
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
