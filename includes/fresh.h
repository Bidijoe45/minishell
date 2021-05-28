/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2021/05/22 18:11:40 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRESH_H
# define FRESH_H

# define NAME "fresh"
# define ART "\
███████╗██████╗ ███████╗███████╗██╗  ██╗\n\
██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n\
█████╗  ██████╔╝█████╗  ███████╗███████║\n\
██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n\
██║     ██║  ██║███████╗███████║██║  ██║\n\
╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n\n"

# include "../resources/libft/libft.h"
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

enum			e_rtype
{
	IN,
	OUT,
	APPEND
};

typedef struct s_while_line {
	char		c[2];
	int			pos;
	int			rd;
	char		*tmp;
	char		*real;
}				t_while_line;

typedef struct s_file
{
	char			*file_name;
	enum e_rtype	type;
	int				fd;
}				t_file;

typedef struct s_export
{
	int			i;
	char		*tmp;
	char		*key;
	char		*value;
}				t_export;

typedef struct s_command
{
	char		*cmd;
	char		**args;
	t_file		**files;
	int			write_to_pipe;
	int			read_from_pipe;
	int			fd[2];
}				t_command;

typedef struct s_echo
{
	int			trail;
	int			i;
	int			j;
	int			print;
	int			already;
}				t_echo;

typedef struct s_fresh
{
	char		*user;
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
	int			waits;
}				t_fresh;

typedef struct s_variable
{
	char	*key;
	char	*value;
}				t_variable;

typedef struct s_extract_files
{
	t_file		**files;
	int			i;
	int			pos;
	int			redirect;
	int			j;
	t_file		*file;
	char		*tmp;
	char		*tmp2;
	char		*key;
	int			n_files;
}				t_extract_files;

typedef struct s_parse_instruction
{
	int			i;
	char		*cmd_name;
	char		*args_str;
	char		**args;
	t_file		**files;
	char		*tmp;
	char		*tmp2;
	t_command	*cmd;
}		t_parse_instruction;

typedef struct s_replace_vars
{
	t_variable	*var;
	char		*ret;
	char		*tmp;
	char		*tmp2;
	char		*key;
	int			i;
	int			pos;
}				t_replace_vars;

typedef struct s_trim_quotes
{
	char		q;
	int			i;
	int			j;
	int			nq;
	char		*ret;
}				t_trim_quotes;

int			is_between_quotes(char *str, int pos);

t_list		*list_new_element(void *content);
void		list_add_back(t_list *list, t_list *new_elem);
void		exec_commands(t_fresh *fresh);
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

void		simple_execute(t_fresh *fresh, t_command *command);
void		write_pipe_execute(t_fresh *fresh, t_command *command,
				int *pid, int *fd[2]);
void		write_read_pipe_execute(t_fresh *fresh, t_command *command,
				int *pid, int *fd[2]);
void		read_pipe_execute(t_fresh *fresh, t_command *command,
				int *pid, int *fd[2]);

void		ft_free_commands_files(t_command *cmd);
void		ft_free_commands_args(t_command *cmd);
void		ft_free_commands(t_fresh *fresh);

void		ft_load_env_vars(t_fresh *fresh, char **envp);

void		ft_execute_commands(t_fresh *fresh);
int			ft_is_builtin(t_fresh *fresh, t_command *command);
int			ft_exec_bin(t_fresh *fresh, t_command *command, int infork);
void		ft_exec_bin_child(t_fresh *fresh, t_command *command);
void		ft_execute_builtin(t_command *command, t_fresh *fresh);
char		*ft_check_if_valid(t_fresh *fresh, t_command *command);
int			check_paths(char **r_path, char **paths, t_command *command);
char		**ft_create_argv(t_command *command, char *path);
char		**ft_list_to_chararr(t_list *list);
void		ft_replace_exit_status(t_fresh *fresh, t_command *command);
int			check_lower_in_a_row_aux(t_fresh *fresh, int i, int *rd);

void		setup_files(t_fresh *fresh, t_command *command, int *i);
int			setup_last_in(t_fresh *fresh);
void		close_files(t_fresh *fresh);
void		export_aux(t_export *export, t_command *command, t_fresh *fresh);
void		export_aux2(t_export *export, t_fresh *fresh);
int			export_while(t_command *command, t_fresh *fresh, t_export *export);
int			validate_variable(char *str);

int			ft_valid_quotes(char *line, int a, int b, int c);
void		replace_variables_key(t_fresh *fresh, int i);
void		replace_variables(t_fresh *fresh);
int			ft_valid_multiline(t_fresh *fresh);
void		ft_while_line(t_fresh *fresh, t_while_line *while_line);
int			is_between_quotes(char *str, int pos);
int			is_between_quotes2(char *str, int pos);
int			between_quotes_pos(int sq, int dq);
int			ft_is_special_char(int c);
void		read_line(t_fresh *fresh);
t_file		**extract_files(char *command, char **command_rpl);
void		extract_simple_redirect(t_extract_files *extract, char *command,
				char **command_rpl);
void		extract_simple_redirect_aux(t_extract_files *extract, char *command,
				char **command_rpl);
void		extract_double_redirect(t_extract_files *extract, char *command,
				char **command_rpl);
int			extract_files_count_files(char *command);
int			check_invalid_redirections(char **cmds);
int			check_chars(char c);
char		*extract_cmd(char *command, char **command_rpl);
int			extract_cmd_count_space_greater_lower(char *command, int i);
int			extract_cmd_count_greater_lower(char *command, int i);
void		trim_q_ftw_aux2(char **line, t_trim_quotes *quotes);
int			trim_count_ftw(char *line);
void		trim_count_ftw_aux(char *line, int *i, char *q, int *nq);
void		ft_trim_args(char ***argsp);
void		ft_parse_cmd_aux(t_fresh *fresh, char **cmds, int n_pipes);
void		ft_parse_instruction(t_fresh *fresh, char *command,
				int rfp, int wtp);
void		ft_parse_instruction_aux(t_fresh *fresh, t_parse_instruction *p_ins,
				char *command);
char		*trim_q_ftw(char *line);
char		*ft_replace_vars(t_fresh *fresh, char *cmds);
void		replace_vars_quotes(t_fresh *fresh, t_command *command);
void		trim_q_ftw_aux3(char *line, t_trim_quotes *quotes);
void		duplicate_list(t_list *src, t_list **dst);
void		free_list(t_list *lst);
void		*ft_malloc(size_t size);
char		*ft_replace2(char *str, char *key, char *word, int n);
#endif
