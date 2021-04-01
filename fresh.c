/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
/*   Updated: 2021/04/01 13:22:52 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fresh.h"
#include "commands/command.h"
#include "music.h"
#include "print/print.h"
#include "parser/parser.h"
#include "list/list.h"

void	ft_initialize(t_fresh *fresh)
{
	fresh->env = NULL;
	fresh->line = NULL;
	fresh->local_vars = NULL;
	fresh->user = NULL;
	fresh->commands = NULL;
}

void	ft_signal(int signum)
{
	return ;
}

void	ft_quit(int signum)
{
	return ;
}

void	ft_load_env_vars(t_fresh *fresh, char **envp)
{
	char 	**split_var;
	int		i;
	t_variable	*var;
	
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
		{
			i++;
			continue ;
		}
		split_var = ft_split(envp[i], '=');
		var = variable_new(ft_strdup(split_var[0]), ft_strdup(split_var[1]));
		if (fresh->env)
			list_add_back(fresh->env, list_new_element(var));
		else
			fresh->env = list_new_element(var);
		i++;
		ft_free_split(split_var);
	}
}

void	ft_execute_commands(t_fresh *fresh)
{
	t_list *list_elem;
	list_elem = fresh->commands;

	while (list_elem)
	{
		t_command *cmd = (t_command *)list_elem->content;
	
		printf("list_cmd: %s\n", cmd->cmd);

		list_elem = list_elem->next;
	}

}

void	ft_free_commands(t_fresh *fresh)
{
	t_list *list_elem;
	list_elem = fresh->commands;
	int	i;

	while (list_elem)
	{
		t_command *cmd = (t_command *)list_elem->content;
		free(cmd->cmd);
		if (cmd->files)
		{
			i = 0;
			while (cmd->files[i])
			{
				free(cmd->files[i]->file_name);
				free(cmd->files[i]);
				i++;
			}
		}
		free(cmd->files);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
		}
		free(cmd->args);
		free(cmd);
		free(list_elem);
		list_elem = list_elem->next;
	}
	fresh->commands = NULL;
}

int		main(int argc, char **argv, char **envp, char **apple)
{
	t_fresh *fresh;
	int		reading;

	//signal(SIGINT, ft_signal);
	//signal(SIGQUIT, ft_signal);
	fresh = malloc(sizeof(t_fresh));
	ft_initialize(fresh);
	ft_load_env_vars(fresh, envp);
	fresh->user = variable_get(fresh->env, "USER")->value;
	ft_print_header(fresh);
	reading = 1;
	while (reading)
	{
		read_line(fresh);
		if (!ft_valid_multiline(fresh))
			ft_print_error(fresh, "Multiline commands not supported\n");
		else
			ft_parse_line(fresh);
		free(fresh->line);
		fresh->line = NULL;
		
		//ejecutar comandos
		ft_execute_commands(fresh);
		ft_free_commands(fresh);
		ft_print_input(fresh);
	}
	//Creo que aqui nunca llega xD
	free(fresh);
}
