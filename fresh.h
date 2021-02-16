/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2021/01/29 12:50:05 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AATANIC_H
# define AATANIC_H

# define NAME "fresh"
# define ART "███████╗██████╗ ███████╗███████╗██╗  ██╗\n██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n█████╗  ██████╔╝█████╗  ███████╗███████║\n██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n██║     ██║  ██║███████╗███████║██║  ██║\n╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n                                        \n"

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./print/colors.h"
# include <sys/errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef enum	e_ctype
{
	simple,
	s_redirect,
	d_redirect,
	r_redirect,
	f_pipe
}				t_ctype;

typedef struct	s_command
{
	char		*cmd;
	char		*arg;
	t_ctype		type;
}				t_command;

typedef struct  s_fresh
{
	char        *user;
	char		*line;
	int			music_pid;
	t_list		*env;
	t_list		*local_vars;
	t_list		*commands;
}               t_fresh;

t_list	*list_new_element(void *content);
void	list_add_back(t_list *list, t_list *new_elem);
void	exec_commands(t_fresh *fresh);
t_command	*command_new(char *cmd, char *arg, t_ctype type);
void	*command_set(t_list **list, t_command *command);
void command_print_list(t_list *list);

#endif