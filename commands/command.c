/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2020/12/22 11:08:37 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void    ft_not_found(char *cmd)
{
    ft_print_color(RESET, "");
    ft_print_color(RED, "Command not found: ");
    ft_print_color(RESET, cmd);
}

int		ft_is_variable(char *command)
{	
	if (ft_strchr(command, '='))
		return (1);
	return (0);
}

//TODO: si una variable local es cambiada tambien tiene que cambiar en export
void    new_local_var(t_fresh *fresh, char *cmd)
{
    char        **split_cmd;
    t_variable  *var;

    split_cmd = ft_split(cmd, '=');
    if (fresh->local_vars)
    {
        variable_set(fresh->local_vars, split_cmd[0], split_cmd[1]);
        variable_mod(fresh->env, split_cmd[0], split_cmd[1]);
    }
    else
        fresh->local_vars = list_new_element(variable_new(split_cmd[0], split_cmd[1]));
    free(split_cmd);
}

//=========TEST ONLY============
static void	list_print(t_list *list)
{
	t_list *elem;

	if (!list)
	{
		ft_printf("lista vacia\n");
		return ;
	}

	ft_printf("--LIST START--\n");
	elem = list;
	while (elem)
	{	
		if (elem->content)
		{
			ft_printf("key: %s\n", ((t_variable *)elem->content)->key);
			ft_printf("value: %s\n", ((t_variable *)elem->content)->value);
		}
		else
			ft_printf("no content\n");
		elem = elem->next;
	}
	ft_printf("--LIST END--\n");
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
    else if (!ft_strncmp(command, "env", 3))
        ft_env(fresh);
    else if (!ft_strncmp(command, "lvars", 4))
        list_print(fresh->local_vars);
    else if (!ft_strncmp(command, "clear", 5))
        ft_clear();
    else if (!ft_strncmp(command, "cd", 2))
        ft_cd(command, fresh);
    else if (!ft_strncmp(command, "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(command, "export", 6))
        ft_export(fresh);
    else if (!ft_strncmp(command, "unset", 5))
        ft_unset();
    else if (!ft_strncmp(command, "env", 3))
        ft_env(fresh);
    else if (!ft_strncmp(command, "echo", 4))
        ft_echo(command, fresh);
    else if (ft_is_variable(command) == 1)
        new_local_var(fresh, command);
    else if (command[0] == '\0')
    {
        ft_print_color(BOLD_GREEN, fresh->user);
	    ft_print_color(GREEN, " > ");
	    ft_print_color(RESET, "");
        return ;
    }
    else
        if (command[0] != '\0')
            ft_not_found(command);
    ft_print_color(BOLD_GREEN, fresh->user);
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}