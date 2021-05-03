/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:00:24 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/03 13:49:05 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/libft/libft.h"
#include "../../includes/fresh.h"
#include "../../includes/parser.h"

/*
 * Check if there's a pipe at the end
 */

int	check_if_pipe_at_end(t_fresh *fresh)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = ft_strlen(fresh->line);
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
			return (1);
		}	
		i++;
	}
	return (0);
}

/*
 * Check if there's a pipe after a semicolon
 */

int	check_if_pipe_after_semicolon(t_fresh *fresh)
{
	int	i;
	int	sc;

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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check if there's a pipe before a semicolon
 */

int	check_if_pipe_before_semicolon(t_fresh *fresh)
{
	int	i;
	int	p;

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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check for a '<' before a semicolon
 */

int	check_lower_before_semicolon(t_fresh *fresh)
{
	int	i;
	int	p;

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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check for a '>' before a semicolon
 */

int	check_greater_before_semicolon(t_fresh *fresh)
{
	int	i;
	int	p;

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
			return (1);
		}
		i++;
	}
	return (0);
}
