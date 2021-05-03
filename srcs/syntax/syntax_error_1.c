/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:41:38 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/03 15:50:04 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/parser.h"

/*
 *	Check for more than one pipe followed by another
 */

int	check_pipe_followed_by_another(t_fresh *fresh)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == '|' && p == 0
			&& !is_between_quotes(fresh->line, i))
			p = 1;
		else if (fresh->line[i] != '|' && fresh->line[i] != ' ' && p == 1)
			p = 0;
		else if (fresh->line[i] == '|' && p == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				fresh->line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check if there's a semicolon at the start
 */

int	check_semicolon_at_start(t_fresh *fresh)
{
	int	i;

	i = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (fresh->line[i] == ';' && i == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				fresh->line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check for more than one semicolon followed by another
 */

int	check_semicolon_followed_by_another(t_fresh *fresh)
{
	int	i;
	int	sc;

	i = -1;
	sc = 0;
	while (fresh->line[++i])
	{
		if (fresh->line[i] == ' ')
			i++;
		if (fresh->line[i] == ';' && sc == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				fresh->line[i]);
			return (1);
		}
		if (fresh->line[i] != ';' && sc == 1)
			sc = 0;
		if (fresh->line[i] == ';'
			&& sc == 0 && !is_between_quotes(fresh->line, i))
			sc = 1;
	}
	return (0);
}

/*
 * Check if there's a '>' at the start
 */

int	check_greater_at_start(t_fresh *fresh)
{
	int	i;
	int	rd;

	i = 0i;
	rd = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (fresh->line[i] == '>' && i == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				fresh->line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check if there are more than 3 candies in a row
 */

int	check_more_than_three_greater_in_a_row(t_fresh *fresh)
{
	int	i;
	int	rd;

	i = 0;
	rd = 0;
	while (fresh->line[++i])
	{
		if (fresh->line[i] == ' ')
			i++;
		if (fresh->line[i] == '>'
			&& !is_between_quotes(fresh->line, i) && rd <= 2)
			rd++;
		else if (fresh->line[i] != '>' && fresh->line[i] != ' ' && rd > 0)
		{
			if (aux_1(fresh, i, 0) == 1)
				return (1);
			rd = 0;
		}
		if (aux_1(fresh, i, rd) == 2)
			return (1);
	}
	return (0);
}
