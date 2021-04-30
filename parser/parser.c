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
		if (line[i] == '\\' && !sq)
		{
			i += 2;
			continue ;
		}
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
			fresh->line = ft_replace(fresh->line, tmp_str, var == NULL ? "" : var->value, 0);
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
	int		rd;
	char	*tmp;
	char	*real;

	pos = 0;
	rd = read(0, c, 1);
	real = NULL;
	if (rd == 0)
	{
		printf("exit\n");
		exit(0);
	}
	while (1)
	{
		c[1] = '\0';
		if (!fresh->line)
			fresh->line = ft_strdup(c);
		else
		{
			if (rd == 0 && !real)
				real = ft_strdup(fresh->line);
			tmp = fresh->line;
			fresh->line = ft_strjoin(fresh->line, c);
			free(tmp);
		}
		if(fresh->line[pos] == '\n')
		{
			if (real)
			{
				free(fresh->line);
				fresh->line = real;
			}
			break ;
		}
		pos++;
		rd = read(0, c, 1);
	}
}

int		ft_is_special_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}


int		is_between_quotes2(char *str, int pos)
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
		if (str[i] == '\\')
		{
			i += 2;
			continue ;
		}
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
	char	*key;

	j = 0;
	i = 0;
	pos = 0;
	*command_rpl = ft_strdup(command);
	while (command[i] != '\0')
	{
		if ((command[i] == '>' || command[i] == '<') && !is_between_quotes(command, i))
		{
			if (command[i + 1] == '>')
				i++;
			pos++;
		}
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
			redirect = i;
			i += 2;
			while(command[i] == ' ')
				i++;
			pos = i;
			while (command[i] != '\0')
			{
				if(command[i] == ' ' && !is_between_quotes(command, i))
					break ;
				i++;
			}
			file = malloc(sizeof(t_file));
			file->file_name = ft_substr(command, pos, i - pos);
			file->type = APPEND;
			files[j] = file;
			tmp = *command_rpl;
			key = ft_substr(command, redirect, i - redirect);
			*command_rpl = ft_replace(tmp, key, "", 1);	
			free(key);
			free(tmp);
			j++;

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
			key = ft_substr(command, redirect, i - redirect);
			*command_rpl = ft_replace(tmp, key, "", 1);	
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
	char *key;

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
			key = ft_substr(command, pos, i - pos);
			*command_rpl = ft_replace(command, key, "", 0);
			free(key);
			return ft_substr(command, pos, i - pos);
		}
	}
	*command_rpl = ft_strdup(command);
	return (ft_strdup(""));
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
		if ((check_chars(cmd[0] && cmd[0] == '|') || check_chars(cmd[l - 1])) &&
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

void	ft_trim_args(char ***argsp)
{
	int		i;
	char	**args;
	char	*tmp;
	char	*tmp2;

	i = 0;
	args = *argsp;
	while (args[i])
	{
		tmp = ft_strtrim(args[i], "'");
		free(args[i]);
		tmp2 = tmp;
		tmp = ft_strtrim(tmp2, "\"");
		free(tmp2);
		args[i] = tmp;
		i++;
	}
}

void	ft_replace_escape(char ***argsp)
{
	int		i;
	char	**args;
	char	*tmp;
	char	*tmp2;

	i = 0;
	args = *argsp;
	while (args[i])
	{
		tmp = ft_replace(args[i], "\\", "", 0);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}

int		trim_count_ftw(char *line)
{
	int nq;
	int i;
	char q;

	nq = 0;
	i = 0;
	q = 0;
	while (line[i])
	{
		if (line[i] == '\\' && q == 0)
		{
			i += 2;
			nq++;
		}
		if ((line[i] == '\'' || line[i] == '"') && q == 0)
		{
			q = line[i];
			nq++;
			i++;
		}
		else
			i++;
		if (line[i] && line[i] == q && q)
		{
			q = 0;
			nq++;
			i++;
		}
	}
	return nq;
}

char	*trim_q_ftw(char *line)
{
	char	q;
	char	*ret;
	int		i;
	int		nq;
	int		j;
	
	nq = trim_count_ftw(line);
	ret = malloc(sizeof(char) * (ft_strlen(line) - nq + 1));
	i = 0;
	j = 0;
	q = 0;
	while (line[i])
	{
		if (line[i] == '\\' && is_between_quotes2(line, i) == 1)
		{
			ret[j++] = line[i++];
		}
		else if (line[i] == '\\' && is_between_quotes2(line, i) == 2)
		{
			if (line[i + 1] && line[i + 1] == '$')
			{
				ret[j++] = line[++i];
				i++;
			}
			else if (line[i + 1] && line[i + 1] == '\\')
			{
				ret[j++] = line[++i];
				i++;
			}
			else if (line[i + 1] && line[i + 1] == '"')
				ret[j++] = line[++i];
			else
				ret[j++] = line[i++];
		}
		else if (line[i] == '\\' && q == 0)
		{
			ret[j++] = line[++i];
			i++;
		}
		else if ((line[i] == '\'' || line[i] == '"') && q == 0)
		{
			q = line[i];
			i++;
		}
		else
			ret[j++] = line[i++];
		if (line[i] && line[i] == q && q)
		{
			q = 0;
			i++;
		}
	}
	ret[j] = '\0';
	return ret;
}
//rfp -> read from pipe
//wtp -> write to pipe
void	ft_parse_instruction(t_fresh *fresh, char *command, int rfp, int wtp)
{
	int i;
	char *cmd_name;
	char *args_str;
	char **args;
	t_file **files;
	char *tmp;
	t_command *cmd;
	
	cmd_name = extract_cmd(command, &tmp);
	command = tmp;
	files = extract_files(command, &tmp);
	free(command);
	command = tmp;
	/* TODO: joder bro estoy hasta los cojones,
	 * hay demasiados leaks y no encuentro ni uno
	 * hay leaks hasta cuando solo le das a enter
	 * pues imaginate si haces export por ejemplo
	 * 1 gb de leaks minimo...
	*/
	args = ft_split_ignore_quotes(command, ' ');
	i = 0;
	while (args[i])
	{
		args[i] = trim_q_ftw(args[i]);
		i++;
	}	
	// TODO:
	// esto da core dump adri (seg fault y esas cosas)
	// ==3927==The signal is caused by a READ memory access 
//	ft_replace_escape(&args);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return ;
	cmd->cmd = trim_q_ftw(cmd_name);
	cmd->files = files;
	cmd->args = args;
	i = 0;
	
	while (cmd->files[i])
	{
		cmd->files[i]->file_name = trim_q_ftw(cmd->files[i]->file_name);
		i++;
	}
	
	cmd->read_from_pipe = rfp;
	cmd->write_to_pipe = wtp;
	command_set(&fresh->commands, cmd);
	free(cmd_name);
	free(tmp);
}

void	ft_parse_cmd(t_fresh *fresh, char *command)
{
	int			i;
	int			n_pipes;
	char 		**cmds;
	t_command	*cmd;
	int command_len;
	
	n_pipes = 0;

	//Comprueba los pipes del principio y final
	i = 0;
	
	cmds = ft_split_ignore_quotes(command, '|');
	/*	
	if (!(check_invalid_redirections(cmds)))
	{
		printf("Error: wrong syntax\n");
		return ;
	}
	*/
	while (cmds[n_pipes])
		n_pipes++;
	if (n_pipes - 1 != 0)
	{
		i = 0;
		while (cmds[i])
		{
			if (i == 0)
				ft_parse_instruction(fresh, cmds[i], 0, 1);
			else if (i == n_pipes - 1)
				ft_parse_instruction(fresh, cmds[i], 1, 0);
			else
				ft_parse_instruction(fresh, cmds[i], 1, 1);
			i++;
		}
	}
	else
		ft_parse_instruction(fresh, command, 0, 0);
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
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
	t_variable	*var;
	char	*ret;
	char	*tmp;
	char	*key;
	int		i;
	int		pos;
	i = 0;
	ret = ft_strdup(cmds);
	while (ret[i])
	{
		if (ret[i] == '\\')
			i += 2;
		if (ret[i] == '$' && ret[i + 1] && ret[i + 1] != '?' && ret[i + 1] != '"' && ret[i + 1] != '\'' && is_between_quotes(ret, i) != 1)
		{
			pos = i;
			pos++;
			while (ret[pos] != ' ' && ret[pos] != '$' && ret[pos] != '"' && ret[pos] != '\'' && ret[pos] !='\\' && ret[pos] != '\0')
				pos++;
			key = ft_substr(ret, i, pos - i);
			tmp = ret;
			var = variable_get(fresh->env, key + 1);
			if (var)
				ret = ft_replace(ret, key, var->value, 0);
			else
				ret = ft_replace(ret, key, "", 0);
			free(tmp);
			free(key);
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

void	ft_parse_line(t_fresh *fresh)
{
	int		i;
	int		cmd_pos;
	char	**cmds;
	char	*tmp;
	int		sc;
	int		p;
	int		rd;

	i = 0;
	tmp = fresh->line;
	fresh->line = ft_strtrim(fresh->line, "\n");
	free(tmp);
	tmp = fresh->line;
	fresh->line = ft_replace_vars(fresh, fresh->line);
	free(tmp);

	//comrpobar si hay mas de un pipe seguidos
	i = 0;
	p = 0;
	int line_len = ft_strlen(fresh->line);
	while (fresh->line[i])
	{
		if (fresh->line[i] == '|' && p == 0 && !is_between_quotes(fresh->line, i))	
			p = 1;
		else if (fresh->line[i] != '|' && fresh->line[i] != ' ' && p == 1)
			p = 0;
		else if (fresh->line[i] == '|' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//Comrprobar si hay ; al inicio
	//Comprobar si hay mas de un ; seguido
	i = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue;
		}
		if (fresh->line[i] == ';' && i == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		if (fresh->line[i] == ';' && sc == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		if (fresh->line[i] != ';' && sc == 1)
			sc = 0;
		if (fresh->line[i] == ';' && sc == 0 && !is_between_quotes(fresh->line, i))
			sc = 1;
		i++;
	}

	//Comprobar si hay > al inicio
	//Comprobar si hay mas de 3 > seguidos
	i = 0;
	rd = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue;
		}
		if (fresh->line[i] == '>' && i == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		if (fresh->line[i] == '>' && !is_between_quotes(fresh->line, i) && rd <= 2)
			rd++;
		else if (fresh->line[i] != '>' && fresh->line[i] != ' ' && rd > 0) 
		{
			if (fresh->line[i] == '<')
			{
				printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
				return ;
			}
			rd = 0;
		}	

		if (rd >= 3)	
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//Comprobar si hay < al inicio
	//Comprobar si hay mas de 3 < seguidos
	i = 0;
	rd = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue;
		}
		if (fresh->line[i] == '<' && i == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		if (fresh->line[i] == '<' && !is_between_quotes(fresh->line, i) && rd <= 2)
			rd++;
		else if (fresh->line[i] != '<' && fresh->line[i] != ' ' && rd > 0)
		{
			if (fresh->line[i] == '<')
			{
				printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
				return ;
			}

			rd = 0;
		}
		
		if (rd >= 2)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//Comprobar si hay pipe al final
	i = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '\\')
		{
			i += 2;
			continue ;
		}
		if (fresh->line[i] == '|' && i == line_len - 1 && !is_between_quotes(fresh->line, i))
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}	
		i++;
	}
	
	//comprobar que despues de un ; no haya un pipe
	i = 0;	
	sc = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ';' && !is_between_quotes(fresh->line, i))
			sc = 1;
		if (fresh->line[i] != ' ' && fresh->line[i] != ';' && fresh->line[i] != '|')
			sc = 0;
		if (fresh->line[i] == '|' && sc == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//comprobar que no haya pipe antes de ;
	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '|' && !is_between_quotes(fresh->line, i))
			p = 1;
		if (fresh->line[i] != ' ' && fresh->line[i] != '|' && fresh->line[i] != ';')
			p = 0;
		if (fresh->line[i] == ';' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}
	
	//comprobar que no haya < antes de ;
	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '<' && !is_between_quotes(fresh->line, i))
			p = 1;
		if (fresh->line[i] != ' ' && fresh->line[i] != '<' && fresh->line[i] != ';')
			p = 0;
		if (fresh->line[i] == ';' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//comprobar que no haya > antes de ;
	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '>' && !is_between_quotes(fresh->line, i))
			p = 1;
		if (fresh->line[i] != ' ' && fresh->line[i] != '>' && fresh->line[i] != ';')
			p = 0;
		if (fresh->line[i] == ';' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}
	
	//comprobar que no haya | antes de > o <
	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '|' && !is_between_quotes(fresh->line, i))
		{
			p = 1;
		}
		if (fresh->line[i] != ' ' && fresh->line[i] != '|' && fresh->line[i] != '>' && fresh->line[i] != '<')
		{
			p = 0;
		}
		if ((fresh->line[i] == '>' || fresh->line[i] == '<') && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}

	//comprobar que no haya > o < antes de | 
	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if ((fresh->line[i] == '>' && fresh->line[i] == '<') && !is_between_quotes(fresh->line, i))
			p = 1;
		if (fresh->line[i] != ' ' && fresh->line[i] != '>' && fresh->line[i] == '<')
			p = 0;
		if (fresh->line[i] == '|' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return ;
		}
		i++;
	}
	cmds = ft_split_ignore_quotes(fresh->line, ';');
	i = 0;
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
