/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:23:23 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/12 10:28:44 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

int	ft_valid_quotes(char *line)
{
	int	dq;
	int	sq;
	int	i;

	dq = 0;
	sq = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && !sq)
			i += 2;
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
	if (dq == 1 || sq == 1)
		return (0);
	else
		return (1);
}

void	replace_variables_key(t_fresh *fresh, int i)
{
	int			end;
	char		*tmp_str;
	char		*tmp;
	t_variable	*var;

	end = i;
	while (fresh->line[end]
		&& fresh->line[end] != ' ' && fresh->line[end] != '\n')
		end++;
	tmp_str = ft_substr(fresh->line, i, end - i);
	var = variable_get(fresh->env, tmp_str + 1);
	tmp = fresh->line;
	if (var == NULL)
		fresh->line = ft_replace(fresh->line, tmp_str, "", 0);
	else
		fresh->line = ft_replace(fresh->line, tmp_str, var->value, 0);
	free(tmp);
	free(tmp_str);
}

void	replace_variables(t_fresh *fresh)
{
	int		i;
	char	*pos;
	int		dq;
	int		sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (fresh->line[i] != '\0')
	{
		if (fresh->line[i] == '\\')
			i += 2;
		if (fresh->line[i] == '"' && sq == 0)
			dq = !dq;
		if (fresh->line[i] == '\'' && dq == 0)
			sq = !sq;
		if (fresh->line[i] == '$')
			replace_variables_key(fresh, i);
		i++;
	}
}

int	ft_valid_multiline(t_fresh *fresh)
{
	t_list	*commands;
	int		valid_q;

	valid_q = ft_valid_quotes(fresh->line);
	if (valid_q == 1)
		return (1);
	else
		return (0);
}

void	ft_while_line(t_fresh *fresh, t_while_line *while_line)
{
	while (1)
	{
		while_line->c[1] = '\0';
		if (!fresh->line)
			fresh->line = ft_strdup(while_line->c);
		else
		{
			if (while_line->rd == 0 && !while_line->real)
				while_line->real = ft_strdup(fresh->line);
			while_line->tmp = fresh->line;
			fresh->line = ft_strjoin(fresh->line, while_line->c);
			free(while_line->tmp);
		}
		if (fresh->line[while_line->pos] == '\n')
		{
			if (while_line->real)
			{
				free(fresh->line);
				fresh->line = while_line->real;
			}
			break ;
		}
		while_line->pos++;
		while_line->rd = read(0, while_line->c, 1);
	}
}

void	read_line(t_fresh *fresh)
{
	t_while_line	while_line;

	while_line.pos = 0;
	while_line.rd = read(0, while_line.c, 1);
	while_line.real = NULL;
	if (while_line.rd == 0)
	{
		printf("exit\n");
		exit(0);
	}
	ft_while_line(fresh, &while_line);
}

int	ft_is_special_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	between_quotes_pos(int sq, int dq)
{
	if (sq)
		return (1);
	if (dq)
		return (2);
	return (0);
}

int	is_between_quotes2(char *str, int pos)
{
	int	i;
	int	sq;
	int	dq;

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
			return (between_quotes_pos(sq, dq));
		i++;
	}
	return (0);
}

int	is_between_quotes(char *str, int pos)
{
	int	i;
	int	sq;
	int	dq;

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
			return (between_quotes_pos(sq, dq));
		i++;
	}
	return (0);
}

int	extract_files_count_files(char *command)
{
	int	i;
	int	files;

	i = 0;
	files = 0;
	while (command[i] != '\0')
	{
		if ((command[i] == '>' || command[i] == '<')
			&& !is_between_quotes(command, i))
		{
			if (command[i + 1] == '>')
				i++;
			files++;
		}
		i++;
	}
	return (files);
}

void	extract_double_redirect(t_extract_files *extract, char *command,
	char **command_rpl)
{
	extract->redirect = extract->i;
	extract->i += 2;
	while (command[extract->i] == ' ')
		extract->i++;
	extract->pos = extract->i;
	while (command[extract->i] != '\0')
	{
		if ((command[extract->i] == ' ' || command[extract->i] == '<'
				|| command[extract->i] == '>')
			&& !is_between_quotes(command, extract->i))
			break ;
		extract->i++;
	}
	extract->file = malloc(sizeof(t_file));
	extract->file->file_name = ft_substr(command, extract->pos,
			extract->i - extract->pos);
	extract->file->type = APPEND;
	extract->files[extract->j] = extract->file;
	extract->tmp = *command_rpl;
	extract->key = ft_substr(command, extract->redirect, extract->i
			- extract->redirect);
	*command_rpl = ft_replace(extract->tmp, extract->key, "", 1);
	free(extract->key);
	free(extract->tmp);
	extract->j++;
}

void	extract_simple_redirect_aux(t_extract_files *extract, char *command,
char **command_rpl)
{
	while (command[extract->i] != '\0')
	{
		if ((command[extract->i] == ' ' || command[extract->i] == '<'
				|| command[extract->i] == '>')
			&& !is_between_quotes(command, extract->i))
			break ;
		extract->i++;
	}
}

void	extract_simple_redirect(t_extract_files *extract, char *command,
	char **command_rpl)
{
	extract->redirect = extract->i;
	extract->i++;
	while (command[extract->i] == ' ')
		extract->i++;
	extract->pos = extract->i;
	extract_simple_redirect_aux(extract, command, command_rpl);
	extract->file = malloc(sizeof(t_file));
	extract->file->file_name = ft_substr(command, extract->pos,
			extract->i - extract->pos);
	if (command[extract->redirect] == '>')
		extract->file->type = OUT;
	else if (command[extract->redirect] == '<')
		extract->file->type = IN;
	extract->files[extract->j] = extract->file;
	extract->tmp = *command_rpl;
	extract->key = ft_substr(command, extract->redirect, extract->i
			- extract->redirect);
	*command_rpl = ft_replace(extract->tmp, extract->key, "", 1);
	free(extract->key);
	free(extract->tmp);
	extract->j++;
}

t_file	**extract_files(char *command, char **command_rpl)
{
	t_extract_files	*extract;

	extract = malloc(sizeof(t_extract_files));
	extract->pos = 0;
	extract->j = 0;
	*command_rpl = ft_strdup(command);
	extract->n_files = extract_files_count_files(command);
	extract->files = malloc(sizeof(t_file *) * extract->n_files + 1);
	extract->files[extract->n_files] = NULL;
	extract->i = 0;
	while (command[extract->i] != '\0')
	{
		while (command[extract->i] == ' ')
			extract->i++;
		if (command[extract->i] == '>' && command[extract->i + 1] == '>'
			&& !is_between_quotes(command, extract->i))
			extract_double_redirect(extract, command, command_rpl);
		else if ((command[extract->i] == '>' || command[extract->i] == '<')
			&& !is_between_quotes(command, extract->i))
			extract_simple_redirect(extract, command, command_rpl);
		else
			extract->i++;
	}
	return (extract->files);
}

int	extract_cmd_count_greater_lower(char *command, int i)
{	
	i++;
	while (command[i] == ' ')
		i++;
	while (command[i] != ' ' && command[i] != '<' && command[i] != '>'
		&& command[i] != '\0')
		i++;
	return (i);
}

int	extract_cmd_count_space_greater_lower(char *command, int i)
{
	while ((command[i] != ' ' && command[i] != '>' && command[i] != '<'
			&& command[i] != '\0' && command[i] != '\n')
		|| (is_between_quotes(command, i) && command[i] != '\0'))
		i++;
	return (i);
}

char	*extract_cmd(char *command, char **command_rpl)
{
	int		i;
	int		pos;
	char	*key;

	i = 0;
	pos = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if ((command[i] == '>' || command[i] == '<')
			&& !is_between_quotes(command, i))
			i = extract_cmd_count_greater_lower(command, i);
		else
		{
			pos = i;
			i = extract_cmd_count_space_greater_lower(command, i);
			key = ft_substr(command, pos, i - pos);
			*command_rpl = ft_replace(command, key, "", 1);
			free(key);
			return (ft_substr(command, pos, i - pos));
		}
	}
	*command_rpl = ft_strdup(command);
	return (ft_strdup(""));
}

int	check_chars(char c)
{
	return (c == '>' || c == '<');
}

int	check_invalid_redirections(char **cmds)
{
	int		l;
	int		i;
	char	*cmd;

	i = 0;
	while (cmds[i])
	{
		cmd = ft_strtrim(cmds[i], " ");
		l = ft_strlen(cmd);
		if ((check_chars(cmd[0] && cmd[0] == '|') || check_chars(cmd[l - 1]))
			&& (!is_between_quotes(cmd, 0) && !is_between_quotes(cmd, l - 1)))
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

void	trim_count_ftw_aux(char *line, int *i, char *q, int *nq)
{
	if (line[*i] && line[*i] == *q && *q)
	{
		*q = 0;
		*nq += 1;
		*i += 1;
	}
}

int	trim_count_ftw(char *line)
{
	int		nq;
	int		i;
	char	q;

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
		trim_count_ftw_aux(line, &i, &q, &nq);
	}
	return (nq);
}

void	trim_q_ftw_aux2(char **line, t_trim_quotes *quotes)
{
	if ((*line)[quotes->i + 1] && (*line)[quotes->i + 1] == '$')
	{
		quotes->ret[quotes->j++] = (*line)[++(quotes->i)];
		quotes->i++;
	}
	else if ((*line)[quotes->i + 1] && (*line)[quotes->i + 1] == '\\')
	{
		quotes->ret[quotes->j++] = (*line)[++(quotes->i)];
		quotes->i++;
	}
	else if ((*line)[quotes->i + 1] && (*line)[quotes->i + 1] == '"')
		quotes->ret[quotes->j++] = (*line)[++(quotes->i)];
	else
		quotes->ret[quotes->j++] = (*line)[quotes->i++];
}

void	trim_q_ftw_aux3(char *line, t_trim_quotes *quotes)
{
	if (line[quotes->i] == '\\' && is_between_quotes2(line, quotes->i) == 1)
		quotes->ret[quotes->j++] = line[quotes->i++];
	else if (line[quotes->i] == '\\' &&
		is_between_quotes2(line, quotes->i) == 2)
		trim_q_ftw_aux2(&line, quotes);
	else if (line[quotes->i] == '\\' && quotes->q == 0)
	{
		quotes->ret[quotes->j++] = line[++(quotes->i)];
		quotes->i++;
	}
	else if ((line[quotes->i] == '\'' || line[quotes->i] == '"')
		&& quotes->q == 0)
	{
		quotes->q = line[quotes->i];
		quotes->i++;
	}
	else
		quotes->ret[quotes->j++] = line[quotes->i++];
	if (line[quotes->i] && line[quotes->i] == quotes->q && quotes->q)
	{
		quotes->q = 0;
		quotes->i++;
	}
}

char	*trim_q_ftw(char *line)
{
	t_trim_quotes quotes;

	quotes.nq = trim_count_ftw(line);
	quotes.ret = malloc(sizeof(char) * (ft_strlen(line) - quotes.nq + 1));
	quotes.i = 0;
	quotes.j = 0;
	quotes.q = 0;
	while (line[quotes.i])
		trim_q_ftw_aux3(line, &quotes);
	quotes.ret[quotes.j] = '\0';
	return (quotes.ret);
}

void	ft_parse_instruction_aux(t_fresh *fresh, t_parse_instruction *p_ins, char *command)
{
	while (p_ins->args[p_ins->i])
	{
		p_ins->tmp2 = p_ins->args[p_ins->i];
		p_ins->args[p_ins->i] = trim_q_ftw(p_ins->args[p_ins->i]);
		free(p_ins->tmp2);
		p_ins->i++;
	}
	p_ins->cmd = malloc(sizeof(t_command));
	if (!p_ins->cmd)
		return ;
	p_ins->cmd->cmd = trim_q_ftw(p_ins->cmd_name);
	p_ins->cmd->files = p_ins->files;
	p_ins->cmd->args = p_ins->args;

	p_ins->i = 0;
	while (p_ins->cmd->files[p_ins->i])
	{
		p_ins->cmd->files[p_ins->i]->file_name = trim_q_ftw(p_ins->cmd->files[p_ins->i]->file_name);
		p_ins->i++;
	}
}

void	ft_parse_instruction(t_fresh *fresh, char *command, int rfp, int wtp)
{
	t_parse_instruction *p_ins;

	p_ins = malloc(sizeof(t_parse_instruction));
	p_ins->cmd_name = extract_cmd(command, &p_ins->tmp);
	command = p_ins->tmp;
	p_ins->files = extract_files(command, &p_ins->tmp);
	free(command);
	command = p_ins->tmp;
	p_ins->args = ft_split_ignore_quotes(command, ' ');
	p_ins->i = 0;
	ft_parse_instruction_aux(fresh, p_ins, command);
	p_ins->cmd->read_from_pipe = rfp;
	p_ins->cmd->write_to_pipe = wtp;
	command_set(&fresh->commands, p_ins->cmd);
	free(p_ins->cmd_name);
	free(p_ins->tmp);
	free(p_ins);
}

void	ft_parse_cmd_aux(t_fresh *fresh, char **cmds, int n_pipes)
{
	int	i;

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

void	ft_parse_cmd(t_fresh *fresh, char *command)
{
	int			i;
	int			n_pipes;
	char		**cmds;
	t_command	*cmd;
	int			command_len;

	n_pipes = 0;
	i = 0;
	cmds = ft_split_ignore_quotes(command, '|');
	while (cmds[n_pipes])
		n_pipes++;
	if (n_pipes - 1 != 0)
		ft_parse_cmd_aux(fresh, cmds, n_pipes);
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

int	check_invalid_pipes(char **cmds)
{
	int		l;
	int		i;
	char	*cmd;

	i = 0;
	while (cmds[i])
	{
		cmd = ft_strtrim(cmds[i], " ");
		l = ft_strlen(cmd);
		if ((cmd[0] == '|' || cmd[l - 1] == '|') && (!is_between_quotes
				(cmd, 0) && !is_between_quotes(cmd, l - 1)))
		{
			free(cmd);
			return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}

void	ft_replace_vars_aux(t_fresh *fresh, char *cmds, t_replace_vars *r_vars)
{
	r_vars->pos = r_vars->i;
	r_vars->pos++;
	while (r_vars->ret[r_vars->pos] != ' ' && r_vars->ret[r_vars->pos] != '$' && r_vars->ret[r_vars->pos]
		!= '"' && r_vars->ret[r_vars->pos] != '\''
		&& r_vars->ret[r_vars->pos] != '\\' && r_vars->ret[r_vars->pos] != '\0')
		r_vars->pos++;
	r_vars->key = ft_substr(r_vars->ret, r_vars->i, r_vars->pos - r_vars->i);
	r_vars->tmp = r_vars->ret;
	r_vars->var = variable_get(fresh->env, r_vars->key + 1);
	if (r_vars->var)
		r_vars->ret = ft_replace(r_vars->ret, r_vars->key, r_vars->var->value, 0);
	else
		r_vars->ret = ft_replace(r_vars->ret, r_vars->key, "", 0);
	free(r_vars->tmp);
	free(r_vars->key);
	r_vars->i = 0;
}

char	*ft_replace_vars(t_fresh *fresh, char *cmds)
{
	t_replace_vars	*r_vars;

	r_vars = malloc(sizeof(t_replace_vars));

	r_vars->i = 0;
	r_vars->ret = ft_strdup(cmds);
	while (r_vars->ret[r_vars->i])
	{
		if (r_vars->ret[r_vars->i] == '\\')
			r_vars->i += 2;
		if (r_vars->ret[r_vars->i] == '$' && r_vars->ret[r_vars->i + 1] && r_vars->ret[r_vars->i + 1] != '?'
			&& r_vars->ret[r_vars->i + 1] != '"' && r_vars->ret[r_vars->i + 1]
			!= '\'' && is_between_quotes(r_vars->ret, r_vars->i) != 1)
			ft_replace_vars_aux(fresh, cmds, r_vars);
		else
			r_vars->i++;
	}
	return (r_vars->ret);
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
	if (syntax_checker(fresh))
		return ;
	cmds = ft_split_ignore_quotes(fresh->line, ';');
	i = -1;
	while (cmds[++i])
		ft_parse_cmd(fresh, cmds[i]);
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
}
