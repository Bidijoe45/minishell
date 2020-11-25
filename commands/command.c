/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/25 12:10:33 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

void    ft_exit()
{
    ft_print_color(BOLD_GREEN, "See you soon!\n\n");
    exit(0);
}

void    ft_cd()
{

}

void    ft_pwd()
{

}

void    ft_export()
{

}

void    ft_unset()
{

}

void    ft_env()
{
    
}

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