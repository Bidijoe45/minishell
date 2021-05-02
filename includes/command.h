/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:46 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/02 13:09:31 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "./fresh.h"

void		ft_parse_command(t_fresh *fresh, t_command *command, t_command *next);
int			ft_is_variable(char *command);

void   		ft_not_found(char *cmd);
t_variable	*variable_new(char *key, char *value);
t_variable	*variable_get(t_list *variables, char *key);
void		variable_set(t_list **variables, char *key, char *value);
void		variable_mod(t_list *variables, char *key, char *value);

#endif
