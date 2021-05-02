/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/02 13:07:35 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/list.h"

void	*command_set(t_list **list, t_command *command)
{
	if (!*list)
		*list = list_new_element(command);
	else
		list_add_back(*list, list_new_element(command));
	return NULL;
}

/*
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

int		ft_is_builtin(t_fresh *fresh, t_command *command)
{
	if (!ft_strncmp(command->cmd, "echo", 4))
		return (1);
	else if (!ft_strncmp(command->cmd, "cd", 2))
		return (ft_cd(fresh, command));
	else if (!ft_strncmp(command->cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(command->cmd, "export", 6))
		ft_export(fresh, command->arg);
	else if (!ft_strncmp(command->cmd, "env", 3))
		return (ft_env(fresh, command));
	else if (!ft_strncmp(command->cmd, "unset", 5))
		return (ft_unset(fresh, command));
	else if (!ft_strncmp(command->cmd, "exit", 4))
		ft_exit(command->arg);
	else
		return (0);
	return (1);
}

void    ft_parse_command(t_fresh *fresh, t_command *command, t_command *next)
{
	int	status;
	int	pid;
	
	if (command->type == simple)
	{
		if (ft_is_builtin(fresh, command))
		{
			;
		}
		else
		{
			if ((status = ft_exec_bin(fresh, command)) == 32512)
				ft_print_error(fresh, "Command not found");
		}
	}
	else if (command->type == f_pipe)
	{
		pipe(command->fd);
		pid = fork();

		if (pid == 0)
		{
			if (fresh->last_fd != 0)
				dup2(fresh->last_fd, 0);
			if (next != NULL)
				dup2(command->fd[1], 1);
			close(command->fd[0]);
			ft_exec_bin(fresh, command);
			exit(errno);
		}
		else
		{
			wait(NULL);
			close(command->fd[1]);
			fresh->last_fd = command->fd[0];
		}
	}
	else if (command->type == s_redirect || command->type == d_redirect)
	{
		pid = fork();

		if (pid == 0)
		{
			command->file = open(command->redirect, O_RDWR | (command->type == s_redirect ? 0 : O_APPEND) | O_CREAT, 0700);
			if (command->file)
				dup2(command->file, 1);
			if ((status = ft_exec_bin(fresh, command)) == 32512)
				ft_print_error(fresh, "Command not found");
			close(command->file);
			exit(errno);
		}
		else
			wait(NULL);
	}
	else if (command->type == r_redirect)
	{
		pid = fork();

		if (pid == 0)
		{
			command->file = open(command->redirect, O_RDWR | (command->type == s_redirect ? 0 : O_APPEND) | O_CREAT, 0700);
			if (command->file)
				dup2(command->file, 0);
			if ((status = ft_exec_bin(fresh, command)) == 32512)
				ft_print_error(fresh, "Command not found");
			close(command->file);
			exit(errno);
		}
		else
			wait(NULL);
	}
}

void	exec_commands(t_fresh *fresh)
{
	int		i;
	t_list *list_elem = fresh->commands;

	i = 0;
	fresh->last_fd = 0;
	while (list_elem)
	{
		t_command *command = ((t_command *)list_elem->content);
		command->index = i;
		ft_parse_command(fresh, command, (t_command *)list_elem->next);
		free(command->arg);
		free(command->cmd);
		if (command->redirect)
			free(command->redirect);
		free(command);
		free(list_elem);
		list_elem = list_elem->next;
		i++;
	}
	fresh->commands = NULL;
	free(fresh->commands);
	ft_print_input(fresh);
}*/
