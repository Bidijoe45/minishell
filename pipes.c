/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:45:49 by alvrodri          #+#    #+#             */
/*   Updated: 2021/01/28 10:21:58 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "./libft/libft.h"

int	main(void)
{
	int		fd[2]; // 0 = reading, 1 = writing
	int		pid;
	char	buf[20];
	char	*new_buf;

	pipe(fd);
	if ((pid = fork()) == -1)
	{
		write(1, "Child could not be created.\n", 29);
		return (0);
	}
	/*
	* If the parent wants to receive data from the child, it should close fd1, and the child should close fd0.
	* If the parent wants to send data to the child, it should close fd0, and the child should close fd1.
	*/
	// echo "hola me llamo Álvaro" | cat -e -> char *command
	char *command = "echo 'hola me llamo Álvaro' | cat -e";
	char *new_command;
	if (pid == 0) // child
	{
		close(fd[1]);
		read(fd[0], buf, 23);
		new_buf = ft_strjoin(" ", buf);
		new_command = ft_strjoin(ft_substr(ft_strchr(command, '|'), 2, ft_strlen(ft_strchr(command, '|') + 2)), new_buf);
		printf("%s", new_command);
	}
	else // parent
	{
		close(fd[0]);
		write(fd[1], "hola me llamo Alvaro\n", 23); // Aquí pasar lo que nos devuelve antes del pipe
	}
}
