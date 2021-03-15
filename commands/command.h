/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:46 by alvrodri          #+#    #+#             */
/*   Updated: 2021/03/14 13:01:19 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_variable
{
	char 	*key;
	char	*value;
}			t_variable;

void		ft_parse_command(t_fresh *fresh, t_command *command, t_command *next);
void		ft_exit(char *exit_code);
int			ft_cd(t_fresh *fresh, t_command *command);
int			ft_pwd();
void		ft_export(t_fresh *fresh, char *cmd);
void		ft_unset();
int			ft_env(t_fresh *fresh, t_command *command);
void		ft_clear();
int			ft_is_variable(char *command);
void		ft_echo(char *cmd, t_fresh *fresh);
void   		ft_not_found(char *cmd);
t_variable	*variable_new(char *key, char *value);
t_variable	*variable_get(t_list *variables, char *key);
void		variable_set(t_list *variables, char *key, char *value);
void		variable_mod(t_list *variables, char *key, char *value);

#endif
