/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2021/04/02 13:56:42 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRESH_H
# define FRESH_H

# define NAME "fresh"
# define ART "███████╗██████╗ ███████╗███████╗██╗  ██╗\n██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n█████╗  ██████╔╝█████╗  ███████╗███████║\n██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n██║     ██║  ██║███████╗███████║██║  ██║\n╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n                                        \n"

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <sys/errno.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>

enum	e_rtype
{
	IN, OUT, APPEND
};

typedef	struct	s_file
{
	char			*file_name;
	enum	e_rtype	type;
	int				fd;
}				t_file;

typedef enum	e_ctype
{
	simple,
}				t_ctype;

typedef struct	s_command
{
	char		*cmd;
	char		**args;
	t_file		**files;
	int			write_to_pipe;
	int			read_from_pipe;
}				t_command;

typedef struct  s_fresh
{
	char        *user;
	char		*line;
	int			music_pid;
	int			last_fd;
	int			cmd_return;
	t_list		*env;
	t_list		*local_vars;
	t_list		*commands;
}               t_fresh;

typedef struct s_variable
{
	char	*key;
	char	*value;
}				t_variable;

t_list		*list_new_element(void *content);
void		list_add_back(t_list *list, t_list *new_elem);
void		exec_commands(t_fresh *fresh);
t_command	*command_new(char *cmd, char *arg, t_ctype type, char *redirect);
void		*command_set(t_list **list, t_command *command);
void		command_print_list(t_list *list);

// commands
int			ft_exit(t_command *command, t_fresh *fresh);
int			ft_echo(t_command *command, t_fresh *fresh);
int			ft_pwd(t_command *command, t_fresh *fresh);

#endif
