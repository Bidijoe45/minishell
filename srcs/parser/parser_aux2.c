/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:40:54 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 17:45:59 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

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
