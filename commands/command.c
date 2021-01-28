/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/01/25 12:59:34 by alvrodri         ###   ########.fr       */
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
	if (split_cmd[1] == NULL)
		return ft_not_found(cmd);
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

int		ft_listsize(t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_list_to_chararr(t_list *list)
{
	char	**arr;
	t_list	*tmp;
	int		size;
	int		i;

	size = ft_listsize(list);
	i = 0;
	arr = malloc(sizeof(char *) * size);
	tmp = list;
	while (tmp)
	{
		arr[i] = ft_strjoin(ft_strjoin(((t_variable *)tmp->content)->key, "="), ((t_variable *)tmp->content)->value);
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void    ft_bash(t_fresh *fresh, char *command)
{
	char    *tmp;
	int     pid;
	int		status;

	tmp = ft_strtrim(command, "\n");
	free(command);
	command = tmp;
	pid = fork();
	if (pid == 0)
		execve("/bin/sh", ft_split(ft_strjoin("/bin/sh -c ", command), ' '), ft_list_to_chararr(fresh->env));
	else
		waitpid(pid, &status, 0);
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
			ft_bash(fresh, command);
	ft_print_color(BOLD_GREEN, fresh->user);
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}