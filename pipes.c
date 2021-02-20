/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:45:49 by alvrodri          #+#    #+#             */
/*   Updated: 2021/02/19 12:07:48 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "./libft/libft.h"

// cat fresh.c | grep a | grep af

int	main(int argc, char **argv, char **env)
{
	int j = 0;
	int		fd[2];
	int fd2[2];
	int		pid;
	int		i;

	i = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp("cat", "cat", "fresh.c", 0);
	}
	else
	{
		while (i < 4 - 2)
		{
			pipe(fd2);
			pid = fork();
	
			if (pid == 0)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd2[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(fd2[1]);
				close(fd2[0]);
				if (j == 0)
				{
					execlp("grep", "grep", "a", 0);
				}
				else
				{
					execlp("grep", "grep", ",", 0);
				}
			}
			i++;
			j++;
		}
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd2[0]);
			close(fd2[1]);
			execlp("grep", "grep", "parse", 0);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			close(fd2[0]);
			close(fd2[1]);
			wait(NULL);
		}
	}
}
