/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
/*   Updated: 2020/11/23 14:15:00 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fresh.h"
#include "commands/command.h"
#include "music.h"
#include "print/print.h"
#include "parser/parser.h"

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
		split_var = ft_split(envp[i], '=');
		if (ft_strncmp(split_var[0], "OLDPWD", 6))
		{
			var = variable_new(split_var[0], split_var[1]);
			if (fresh->env)
				list_add_back(fresh->env, list_new_element(var));
			else
				fresh->env = list_new_element(var);
		}
		i++;
		free(split_var);
	}
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

int		main(int argc, char **argv, char **envp, char **apple)
{
	t_fresh *fresh;
	int		reading;

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	fresh = malloc(sizeof(t_fresh));
//	ft_play_music(fresh);
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
		ft_print_input(fresh);
	}
	
	free(fresh);
}
