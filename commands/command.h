/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:46 by alvrodri          #+#    #+#             */
/*   Updated: 2020/12/18 12:17:40 by apavel           ###   ########.fr       */
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

void    ft_parse_command(t_fresh *fresh);
void	ft_exit();
void	ft_cd(char *cmd, t_fresh *fresh);
void	ft_pwd();
void	ft_export(t_fresh *fresh);
void	ft_unset();
void	ft_env(t_fresh *fresh);
void	ft_clear();
int		ft_is_variable(char *command);
void    	ft_parse_command(t_fresh *fresh);
void		ft_exit();
void		ft_cd(char *cmd, t_fresh *fresh);
void		ft_pwd();
void		ft_export(t_fresh *fresh);
void		ft_unset();
void		ft_env(t_fresh *fresh);
void		ft_clear();
void		ft_echo(char *cmd, t_fresh *fresh);
t_variable	*variable_new(char *key, char *value);
t_variable	*variable_get(t_list *variables, char *key);
void		variable_set(t_list *variables, char *key, char *value);

#endif