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
#include "utils/utils.h"

void	ft_print_header(t_fresh *fresh)
{
	ft_print_color(BOLD_GREEN, ART);
	ft_print_color(BOLD_GREEN, fresh->user);
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
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
		var = variable_new(split_var[0], split_var[1]);
		if (fresh->env)
			list_add_back(fresh->env, list_new_element(var));
		else
			fresh->env = list_new_element(var);
		i++;
	}
}

void	read_line(t_fresh *fresh)
{
	char	c[2];
	int		pos;
	char	*tmp;

	pos = 0;
	while (read(0, c, 1) > 0)
	{
		c[1] = '\0';
		if (!fresh->line)
			fresh->line = ft_strdup(c);
		else
		{
			tmp = fresh->line;
			fresh->line = ft_strjoin(fresh->line, c);
			free(tmp);
		}
		if(fresh->line[pos] == '\n')
		{
			ft_parse_command(fresh);
			free(fresh->line);
			fresh->line = NULL;
			tmp = NULL;
			pos = -1;
		}
		pos++;
	}
}

void	ft_initialize(t_fresh *fresh)
{
	fresh->env = NULL;
	fresh->line = NULL;
	fresh->local_vars = NULL;
	fresh->user = NULL;
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

	fresh = malloc(sizeof(t_fresh));
	ft_initialize(fresh);
	ft_load_env_vars(fresh, envp);
	fresh->user = variable_get(fresh->env, "USER")->value;
	ft_print_header(fresh);
	read_line(fresh);
	free(fresh);
}
