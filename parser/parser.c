#include "../fresh.h"
#include "../print/print.h"
#include "../commands/command.h"
#include "parser.h"

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

void replace_variables(t_fresh *fresh)
{
	int i = 0;
	char *pos;
	int dq;
	int sq;
	int end;
	char *tmp_str;
	char	*tmp;
	t_variable *var;

	dq = 0;
	sq = 0;
	end = 0;

	while (fresh->line[i] != '\0')
	{
		if (fresh->line[i] == '\\')
			i += 2;
		if (fresh->line[i] == '"' && sq == 0)
			dq = !dq;
		if (fresh->line[i] == '\'' && dq == 0)
			sq = !sq;
		if (fresh->line[i] == '$')
		{
			end = i;
			while (fresh->line[end] && fresh->line[end] != ' ' && fresh->line[end] != '\n')
				end++;
			tmp_str = ft_substr(fresh->line, i, end - i);
			var = variable_get(fresh->env, tmp_str + 1);
			tmp = fresh->line;
			fresh->line = ft_replace(fresh->line, tmp_str, var == NULL ? "" : var->value);
			free(tmp);
			free(tmp_str);
		}
		i++;
	}
}

int		ft_valid_multiline(t_fresh *fresh)
{
	t_list *commands;
	int  valid_q;

	valid_q = ft_valid_quotes(fresh->line);
	if (valid_q == 1)
		return (1);
	else
		return (0);
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
			break ;
		pos++;
	}
}

int		ft_is_special_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int		is_between_quotes(char *str, int pos)
{
	int i;
	int sq;
	int dq;

	if (!str || !*str)
		return (0);
	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && dq == 0)
			sq = !sq;
		if (str[i] == '"' && sq == 0)
			dq = !dq;
		if (i == pos)
		{
			if (sq)
				return (1);
			if (dq)
				return (2);
			return (0);
		}
		i++;
	}
	return (0);
}

t_file	**extract_files(char *command, char **command_rpl)
{
	t_file	**files;
	int		i;
	int		pos;
	int		redirect;
	int		j;
	t_file *file;
	char	*tmp;
	char	*tmp2;

	j = 0;
	i = 0;
	pos = 0;
	*command_rpl = ft_strdup(command);
	while (command[i] != '\0')
	{
		if ((command[i] == '>' || command[i] == '<') && !is_between_quotes(command, i))
			pos++;	
		i++;
	}
	files = malloc(sizeof(t_file *) * pos + 1);
	files[pos] = NULL;
	i = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if (command[i] == '>' && command[i + 1] == '>' && !is_between_quotes(command, i))
		{

		}
		else if ((command[i] == '>' || command[i] == '<') && !is_between_quotes(command, i))
		{
			redirect = i;
			i++; 
			while (command[i] == ' ')
				i++;
			pos = i;
			while (command[i] != '\0')
			{
				if (command[i] == ' ' && !is_between_quotes(command, i))
						break ;
				i++;
			}
			file = malloc(sizeof(t_file));
			file->file_name = ft_substr(command, pos, i - pos);
			if (command[redirect] == '>')
				file->type = OUT;
			else if (command[redirect] == '<')
				file->type = IN;
			files[j] = file;
			tmp = *command_rpl;
			char *key = ft_substr(command, redirect, i - redirect);
			*command_rpl = ft_replace(tmp, key, "");
			free(key);
			free(tmp);
			j++;
		}
		i++;
	}
	return (files);
}

char	*extract_cmd(char *command, char **command_rpl)
{
	int	i;
	int	pos;
	int	next_is_file;

	i = 0;
	pos = 0;
	next_is_file = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if ((command[i] == '>' || command[i] == '<') && !is_between_quotes(command, i))
		{
			i++;
			while (command[i] == ' ')
				i++;
			while (command[i] != ' ' && command[i] != '<' && command[i] != '>'
				&& command[i] != '\0')
				i++;
		}
		else
		{
			pos = i;
			while ((command[i] != ' ' && command[i] != '>' && command[i] != '<'
				&& command[i] != '\0' && command[i] != '\n') || (is_between_quotes(command, i) && command[i] != '\0'))
				i++;
			char *key = ft_substr(command, pos, i - pos);
			*command_rpl = ft_replace(command, key, "");
			free(key);
			return ft_substr(command, pos, i - pos);
		}
	}
	return ft_substr(command, pos, i - pos);
}

char	*extract_args(char *command)
{
	int	i;
	int	pos;
	int	next_is_file;
	
	i = 0;
	pos = 0;
	next_is_file = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if ((command[i] == '>' || command[i] == '<') && !is_between_quotes(command, i))
		{
			i++;
			while (command[i] == ' ')
				i++;
			while (command[i] != ' ' && command[i] != '<' && command[i] != '>'
				&& command[i] != '\0')
				i++;
		}
		else
		{
			while (command[i] != ' ' && command[i] != '>' && command[i] != '<'
				&& command[i] != '\0' && command[i] != '\n' )
				i++;
			pos = i;
			while ((command[i] != '>' && command[i] != '<'
				&& command[i] != '\0' && command[i] != '\n') || is_between_quotes(command, i))
				i++;
			
			return ft_substr(command, pos, i - pos);
		}
	}
	return ft_substr(command, pos, i - pos);
}

int		check_chars(char c)
{
	return (c == '>' || c == '<');
}

int		check_invalid_redirections(char **cmds)
{
	int		l;
	int		i;
	char	*cmd;
	
	i = 0;
	while (cmds[i])
	{
		cmd = ft_strtrim(cmds[i], " ");
		l = ft_strlen(cmd);
		if ((check_chars(cmd[0]) || check_chars(cmd[l - 1])) &&
				(!is_between_quotes(cmd, 0) && !is_between_quotes(cmd, l - 1)))
		{
			free(cmd);
			return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}

void	ft_parse_cmd(t_fresh *fresh, char *command)
{
	int			i;
	int			j;
	int			n_pipes;
	char 		**cmds;
	char		*cmd_name;
	char		*args_str;
	char		**args;
	t_file		**files;
	char		*tmp;
	t_command	*cmd;
	
	n_pipes = 0;
	cmds = ft_split_ignore_quotes(command, '|');
	if (!(check_invalid_redirections(cmds)))
	{
		printf("Error: wrong syntax\n");
		return ;
	}
	while (cmds[n_pipes])
		n_pipes++;
	if (n_pipes - 1 != 0)
	{
	
	}
	else
	{
		cmd_name= extract_cmd(command, &tmp);
		command = tmp;
		files = extract_files(command, &tmp);
		free(command);
		command = tmp;
		args = ft_split_ignore_quotes(command, ' ');
		cmd = malloc(sizeof(t_command));
		if (!cmd)
			return ;
		cmd->cmd = cmd_name;
		cmd->files = files;
		cmd->args = args;
		printf("command: |%s|\n", cmd->cmd);
		i = 0; /* TODO: ARREGLAR QUE SI PONGO "ls > >" DA SEGFAULT PORQUE NO ALOCAMOS UN PAR DE COSAS! */
		while (files[i])
		{
			free(files[i]->file_name);
			free(files[i]);
			i++;
		}
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		free(files);
		free(tmp);
		free(cmd);
	}
	ft_free_split(cmds);
}

int		check_invalid_pipes(char **cmds)
{
	int		l;
	int		i;
	char	*cmd;
	
	i = 0;
	while (cmds[i])
	{
		cmd = ft_strtrim(cmds[i], " ");
		l = ft_strlen(cmd);
		if ((cmd[0] == '|' || cmd[l - 1] == '|') &&
				(!is_between_quotes(cmd, 0) && !is_between_quotes(cmd, l - 1)))
		{
			free(cmd);
			return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}

char	*ft_replace_vars(t_fresh *fresh, char *cmds)
{
	char	*ret;
	char	*tmp;
	char	*key;
	int		i;
	int		pos;

	i = 0;
	ret = ft_strdup(cmds);
	while (ret[i])
	{
		if (ret[i] == '$' && is_between_quotes(ret, i) != 1)
		{
			pos = i;
			pos++;
			while (ret[pos] != ' ' && ret[pos] != '$' && ret[pos] != '"' && ret[pos] != '\0')
				pos++;
			key = ft_substr(ret, i, pos - i);
			tmp = ret;
			ret = ft_replace(ret, key, variable_get(fresh->env, key + 1)->value);
			free(tmp);
			free(key);
			i = 0;
		}
		else
			i++;
	}
	printf("|%s|\n", ret);
	return (ret);
}

void	ft_parse_line(t_fresh *fresh)
{
	int		i;
	int		cmd_pos;
	char	**cmds;
	char	*tmp;

	i = 0;
	tmp = fresh->line;
	fresh->line = ft_strtrim(fresh->line, "\n");
	free(tmp);
	tmp = fresh->line;
	fresh->line = ft_replace_vars(fresh, fresh->line);
	free(tmp);
	cmds = ft_split_ignore_quotes(fresh->line, ';');
	if (!check_invalid_pipes(cmds))
	{
		printf("Error: wrong syntax\n");
		return ;
	}
	while (cmds[i])
	{
		ft_parse_cmd(fresh, cmds[i]);
		i++;
	}
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
