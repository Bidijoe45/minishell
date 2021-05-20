/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:44:38 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/18 14:17:56 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

void	trim_q_ftw_aux3(char *line, t_trim_quotes *quotes)
{
	if (line[quotes->i] == '\\' && is_between_quotes2(line, quotes->i) == 1)
		quotes->ret[quotes->j++] = line[quotes->i++];
	else if (line[quotes->i] == '\\'
		&& is_between_quotes2(line, quotes->i) == 2)
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
	t_trim_quotes	quotes;

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

void	ft_parse_instruction_aux(t_fresh *fresh, t_parse_instruction *p_ins,
	char *command)
{
	while (p_ins->args[p_ins->i])
	{
		p_ins->tmp2 = p_ins->args[p_ins->i];
		p_ins->args[p_ins->i] = ft_strdup(p_ins->args[p_ins->i]);
		free(p_ins->tmp2);
		p_ins->i++;
	}
	p_ins->cmd = malloc(sizeof(t_command));
	if (!p_ins->cmd)
		return ;
	p_ins->cmd->cmd = ft_strdup(p_ins->cmd_name);
	
	p_ins->cmd->files = p_ins->files;
	p_ins->cmd->args = p_ins->args;
	p_ins->i = 0;
	while (p_ins->cmd->files[p_ins->i])
	{
		p_ins->cmd->files[p_ins->i]->file_name
			= p_ins->cmd->files[p_ins->i]->file_name;
		p_ins->i++;
	}
}

void	ft_parse_instruction(t_fresh *fresh, char *command, int rfp, int wtp)
{
	t_parse_instruction	p_ins;

	p_ins.cmd_name = extract_cmd(command, &p_ins.tmp);
	command = p_ins.tmp;
	p_ins.files = extract_files(command, &p_ins.tmp);
	free(command);
	command = p_ins.tmp;
	p_ins.args = ft_split_ignore_quotes(command, ' ');
	p_ins.i = 0;
	ft_parse_instruction_aux(fresh, &p_ins, command);
	p_ins.cmd->read_from_pipe = rfp;
	p_ins.cmd->write_to_pipe = wtp;
	command_set(&fresh->commands, p_ins.cmd);
	free(p_ins.cmd_name);
	free(p_ins.tmp);
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
