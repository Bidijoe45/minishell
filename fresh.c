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

void	ft_print_error(t_fresh *fresh, char *error_str)
{
    ft_print_color(RESET, "");
    ft_print_color(RED, "Error: ");
    ft_print_color(RESET, error_str);
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
		free(split_var);
	}
}

int		ft_valid_quotes(char *line)
{
	int dq;
	int sq;
	int i;

	dq = 0;
	sq = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && dq == 0 && sq == 0)
			dq = 1;
		else if (line[i] == '"' && dq == 1)
			dq = 0;

		if (line[i] == '\'' && sq == 0 && dq == 0)
			sq = 1;
		else if (line[i] == '\'' && sq == 1)
			sq = 0;

		i++;
	}
	return (dq == 1 || sq == 1) ? 0 : 1;
}

void ft_split_commands(t_fresh *fresh, char *line)
{
	int i = 0;
	int start = 0;
	char *command;
	char *argument;
	char arg_f = 0;
	int dq = 0;
	int sq = 0;
	int end = 0;
	t_ctype type = simple;

	argument = NULL;
	while (!end)
	{
		while (line[i] == ' ')
			i++;
		start = i;
		while (line[i] != '\0' && line[i] != ' ' && line[i] != ';')
			i++;
		command = ft_substr(line, start, i - start);
		if (command[0] == '\0')
			break ;
		if (line[i] != ';')
		{
			while (line[i] == ' ')
				i++;
			start = i;
			while (line[i] != '\0')
			{
				if (line[i] == '"' && sq == 0)
					dq = !dq;
				if (line[i] == '\'' && dq == 0)
					sq = !sq;
				if (line[i] == ';' && (sq == 0 && dq == 0))
					break ;
				else if (line[i] == '|' && (sq == 0 && dq == 0))
				{
					type = f_pipe;
					break ;
				}
				else if (line[i] == '>' && line[i+1] == '>' && (sq == 0 && dq == 0))
				{
					type = d_redirect;
					break ;
				}
				else if (line[i] == '>' && (sq == 0 && dq == 0))
				{
					type = s_redirect;
					break ;
				}
				else if (line[i] == '<' && (sq == 0 && dq == 0))
				{
					type = r_redirect;
					break ;
				}
				i++;
			}
			argument = ft_substr(line, start, i - start);
		}
		if (!argument)
			argument = ft_strdup("");
		if (*command != '\n')
			command_set(&fresh->commands, command_new(command, argument, type));
		i++;
		if (line[i] == '\0' || (line[i] == '\n' && line[i + 1] == '\0'))
			break ;
	}
	exec_commands(fresh);
}

void	ft_print_input(t_fresh *fresh)
{
	ft_print_color(BOLD_GREEN, fresh->user);
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}

void	exec_commands(t_fresh *fresh)
{
	t_list *list_elem = fresh->commands;

	if (list_elem == NULL)
		ft_print_input(fresh);
	while (list_elem)
	{
		t_command *command = ((t_command *)list_elem->content);

		ft_parse_command(fresh, command);
		list_elem = list_elem->next;
	}
	fresh->commands = NULL;
}

void	ft_mini_parse(t_fresh *fresh)
{
	t_list *commands;
	int commands_n;
	int  valid_q;
	
	valid_q = ft_valid_quotes(fresh->line);
	if (valid_q == 1)
	{	
		ft_split_commands(fresh, fresh->line);
	}
	else
	{
		ft_print_error(fresh, "Multiline commands not supported\n");
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
			ft_mini_parse(fresh);
			//ft_parse_command(fresh);
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
	fresh->commands = NULL;
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

void	ft_play_music(t_fresh *fresh)
{
	fresh->music_pid = fork();
	if (!fresh->music_pid)
	{
		system("afplay ./resources/music.mp3");
		exit(0);
	}
}

int		main(int argc, char **argv, char **envp, char **apple)
{
	t_fresh *fresh;

	fresh = malloc(sizeof(t_fresh));
//	ft_play_music(fresh);
	ft_initialize(fresh);
	ft_load_env_vars(fresh, envp);
	fresh->user = variable_get(fresh->env, "USER")->value;
	ft_print_header(fresh);
	read_line(fresh);
	free(fresh);
}
