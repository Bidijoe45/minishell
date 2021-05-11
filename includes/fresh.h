/* ************************************************************************** */
  /*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2021/05/10 13:42:51 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRESH_H
# define FRESH_H

# define NAME "fresh"
# define ART "███████╗██████╗ ███████╗███████╗██╗  ██╗\n██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n█████╗  ██████╔╝█████╗  ███████╗███████║\n██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n██║     ██║  ██║███████╗███████║██║  ██║\n╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n                                        \n"

# include "../resources/libft/libft.h"
# include "../resources/ft_printf/ft_printf.h"
# include "./signal.h"
# include <sys/errno.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

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
	int			fd[2];
}				t_command;

typedef struct	s_echo
{
	int			trail;
	int			i;
	int			j;
	int			print;
	int			already;
}				t_echo;

typedef struct  s_fresh
{
	char        *user;
	char		*line;
	int			music_pid;
	int			last_fd;
	t_file		*last_in;
	t_file		*last_out;
	int			fd_in;
	int			fd_out;
	int			cmd_return;
	int			pid;
	t_list		*env;
	t_list		*local_vars;
	t_list		*commands;
}               t_fresh;

typedef struct s_variable
{
	char	*key;
	char	*value;
}				t_variable;

int			is_between_quotes(char *str, int pos);

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
int			ft_cd(t_command *command, t_fresh *fresh);
int			ft_env(t_command *command, t_fresh *fresh);
int			ft_export(t_command *command, t_fresh *fresh);
int			ft_unset(t_command *command, t_fresh *fresh);

int			syntax_checker(t_fresh *fresh);
int			check_pipe_followed_by_another(t_fresh *fresh);
int			check_semicolon_followed_by_another(t_fresh *fresh);
int			check_semicolon_at_start(t_fresh *fresh);
int			check_greater_at_start(t_fresh *fresh);
int			check_more_than_three_greater_in_a_row(t_fresh *fresh);
int			check_if_pipe_at_end(t_fresh *fresh);
int			check_if_pipe_after_semicolon(t_fresh *fresh);
int			check_if_pipe_before_semicolon(t_fresh *fresh);
int			check_lower_before_semicolon(t_fresh *fresh);
int			check_greater_before_semicolon(t_fresh *fresh);
int			check_greater_lower_before_pipe(t_fresh *fresh);
int			check_pipe_before_greater_lower(t_fresh *fresh);
int			check_lower_in_a_row(t_fresh *fresh);
int			check_lower_greater_at_end(t_fresh *fresh);
int			check_pipe_at_start(t_fresh *fresh);

int			aux_1(t_fresh *fresh, int i);
int			aux_2(t_fresh *fresh, int i, int rd);

int			ft_exec_bin(t_fresh *fresh, t_command *command);

void		simple_execute(t_fresh *fresh, t_command *command);
void		write_pipe_execute(t_fresh *fresh, t_command *command, int *pid, int *fd[2]);
void		write_read_pipe_execute(t_fresh *fresh, t_command *command, int *pid, int *fd[2]);
void		read_pipe_execute(t_fresh *fresh, t_command *command, int *pid, int *fd[2]);

void		ft_free_commands_files(t_command *cmd);
void		ft_free_commands_args(t_command *cmd);
void		ft_free_commands(t_fresh *fresh);

void		ft_load_env_vars(t_fresh *fresh, char **envp);

void		ft_execute_commands(t_fresh *fresh);
int			ft_is_builtin(t_fresh *fresh, t_command *command);
int			ft_exec_bin(t_fresh *fresh, t_command *command);
void		ft_exec_bin_child(t_fresh *fresh, t_command *command);
void		ft_execute_builtin(t_command *command, t_fresh *fresh);
char		*ft_check_if_valid(t_fresh *fresh, t_command *command);
int			check_paths(char **r_path, char **paths, t_command *command);
char		**ft_create_argv(t_command *command, char *path);
char		**ft_list_to_chararr(t_list *list);
void		ft_replace_exit_status(t_fresh *fresh, t_command *command);
int			check_lower_in_a_row_aux(t_fresh *fresh, int i, int *rd);

void		setup_files(t_fresh *fresh, t_command *command, int *i);
void		setup_last_in(t_fresh *fresh);
void		close_files(t_fresh *fresh);
#endif
