/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:46 by alvrodri          #+#    #+#             */
/*   Updated: 2020/12/15 12:24:33 by apavel           ###   ########.fr       */
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

void    	ft_parse_command(t_fresh *fresh);
void		ft_exit();
void		ft_cd(char *cmd, t_fresh *fresh);
void		ft_pwd();
void		ft_export(t_fresh *fresh);
void		ft_unset();
void		ft_env(t_fresh *fresh);
void		ft_clear();
t_variable	*ft_new_variable(char *key, char *value);
void		ft_set_variable(t_list *variables, t_variable *var);
t_variable	*ft_get_variable(t_list *variables, char *key);

#endif