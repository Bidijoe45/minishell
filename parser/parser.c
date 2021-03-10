#include "../fresh.h"
#include "../print/print.h"

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
	char	*tmp;
	char *command;
	char *argument;
	char arg_f = 0;
	int dq = 0;
	int sq = 0;
	int end = 0;
	char	*redirect;
	t_ctype type = simple;

	argument = NULL;
	while (!end)
	{
		while (line[i] == ' ')
			i++;
		start = i;
		while (line[i] != '\0' && line[i] != ' ' && line[i] != ';')
		{
			if (line[i] == ';' && line[i - 1] == '\\')
				i++;
			i++;
		}
		command = ft_substr(line, start, i - start);
		if (command[0] == '\0')
			break ;
		if (line[i] != ';' || (line[i] == ';' && line[i - 1] == '\\'))
		{
			while (line[i] == ' ')
				i++;
			start = i;
			while (line[i] != '\0')
			{
				if (line[i] == '\\')
					i+=2;
				if (line[i] == '"' && sq == 0)
					dq = !dq;
				if (line[i] == '\'' && dq == 0)
					sq = !sq;
				if (((line[i] == ';' )) && (sq == 0 && dq == 0) )
					break ;
				else if (line[i] == '|' && (sq == 0 && dq == 0))
				{
					type = f_pipe;
					break ;
				}
				else if (line[i] == '>' && line[i+1] == '>' && (sq == 0 && dq == 0))
				{
					type = d_redirect;
					redirect = ft_strdup(ft_strnstr(line, ">>", ft_strlen(line)) + 2);
					tmp = redirect;
					redirect = ft_strtrim(redirect, "\n");
					free(tmp);
					tmp = redirect;
					redirect = ft_strtrim(redirect, " ");
					free(tmp);
					end = 1;
					break ;
				}
				else if (line[i] == '>' && (sq == 0 && dq == 0))
				{
					type = s_redirect;
					redirect = ft_strdup(ft_strchr(line, '>') + 1);
					tmp = redirect;
					redirect = ft_strtrim(redirect, "\n");
					free(tmp);
					tmp = redirect;
					redirect = ft_strtrim(redirect, " ");
					free(tmp);
					end = 1;
					break ;
				}
				else if (line[i] == '<' && (sq == 0 && dq == 0))
				{
					type = r_redirect;
					end = 1;
					break ;
				}
				i++;
			}
			argument = ft_substr(line, start, i - start);
		}
		if (!argument)
			argument = ft_strdup("");
		if (*command != '\n')
			command_set(&fresh->commands, command_new(command, argument, type, redirect));
		i++;
		if (line[i] == '\0' || (line[i] == '\n' && line[i + 1] == '\0'))
			break ;
	}
	/*
	* replace_env(fresh);
	*/
	exec_commands(fresh);
}

void	ft_valid_multiline(t_fresh *fresh)
{
	t_list *commands;
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
			ft_valid_multiline(fresh);
			free(fresh->line);
			fresh->line = NULL;
			tmp = NULL;
			pos = -1;
		}
		pos++;
	}
}
