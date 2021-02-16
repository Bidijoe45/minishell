/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/01/29 12:49:58 by apavel           ###   ########.fr       */
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

t_command	*command_new(char *cmd, char *arg, t_ctype type)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	command->cmd = cmd;
	command->arg = arg;
	command->type = type;
	return (command);
}

void	*command_set(t_list **list, t_command *command)
{
	if (!*list)
		*list = list_new_element(command);
	else
		list_add_back(*list, list_new_element(command));
}

//=========TEST ONLY============
void	command_print_list(t_list *list)
{
	if (!list)
		printf("lista de comandos vacia\n");
	
	t_list *elem;

	elem = list;
	while (elem)
	{
		t_command *cmd = (t_command *)elem->content;
		printf("--command--\n");
		printf("cmd: %s\n",	cmd->cmd);
		printf("arg: %s\n",	cmd->arg);
		printf("type: %u\n", cmd->type);
		printf("\n");
		elem = elem->next;
	}
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

void    ft_parse_command(char *command, char *argument)
{
	printf("||%s||\n", command);
}