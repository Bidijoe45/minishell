/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/30 12:06:47 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void    ft_not_found(char *cmd)
{
    ft_print_color(RESET, "");
    ft_print_color(RED, "Command not found: ");
    ft_print_color(RESET, cmd);
    ft_print_color(RESET, "\n\n");
}

void    ft_parse_command(t_fresh *fresh)
{
    char    *command;
    int     i;

    i = 0;
    while (ft_isspace(fresh->line[i]))
        i++;
    command = ft_strtrim(&fresh->line[i], " ");
    if (!ft_strncmp(command, "exit", 4))
        ft_exit();
    if (!ft_strncmp(command, "clear", 5))
        ft_clear();
    else if (!ft_strncmp(command, "cd", 2))
        ft_cd();
    else if (!ft_strncmp(command, "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(command, "export", 6))
        ft_export();
    else if (!ft_strncmp(command, "unset", 5))
        ft_unset();
    else if (!ft_strncmp(command, "env", 3))
        ft_env();
    else if (command[0] == '\0')
        return ;
    else
        ft_not_found(command);
}