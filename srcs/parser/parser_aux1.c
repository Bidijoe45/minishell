/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:39:55 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 17:45:48 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

int	ft_valid_quotes(char *line, int dq, int sq, int i)
{
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
	int		dq;
	int		sq;

	i = 0;
	dq = 0;
	sq = 0;
	printf("llega!\n");
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
	int		valid_q;

	valid_q = ft_valid_quotes(fresh->line, 0, 0, 0);
	if (valid_q == 1)
		return (1);
	else
	{
		fresh->cmd_return = 1;
		return (0);
	}
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
