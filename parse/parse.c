#include "fresh.h"

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