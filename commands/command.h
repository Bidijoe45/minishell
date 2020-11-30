/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:46 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/30 12:37:05 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

#ifndef COMMAND_H
# define COMMAND_H

void    ft_parse_command(t_fresh *fresh);
void	ft_exit();
void	ft_cd(char *cmd, t_fresh *fresh);
void	ft_pwd();
void	ft_export();
void	ft_unset();
void	ft_env();
void	ft_clear();

#endif