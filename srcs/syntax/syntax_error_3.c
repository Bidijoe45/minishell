/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:41:38 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/03 14:12:00 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/parser.h"

/*
 * Check for '>' | '<' before pipe
 */

int	check_greater_lower_before_pipe(t_fresh *fresh)
{
	int	i;
	int	p;

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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check for '|' before '<' or '>'
 */

int	check_pipe_before_greater_lower(t_fresh *fresh)
{
	int	i;
	int	p;

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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Check if for '<' in a row
 */
int	check_lower_in_a_row(t_fresh *fresh)
{
	int i;
	int	rd;

	i = 0;
	rd = 0;
	while (fresh->line[i])
	{
		if (fresh->line[i] == ' ')
		{
			i++;
			continue;
		}
		if (fresh->line[i] == '<' && !is_between_quotes(fresh->line, i) && rd <= 1)
			rd++;
		else if (fresh->line[i] != '<' && fresh->line[i] != ' ' && rd > 0) 
		{
			if (fresh->line[i] == '<')
			{
				printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
				return (1);
			}
			rd = 0;
		}	
		if (rd >= 2)	
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return (1);
		}
		i++;
	}
	return (0);

}

int check_lower_greater_at_end(t_fresh *fresh)
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
		if ((fresh->line[i] == '<' || fresh->line[i] == '>') && i == line_len - 1 && !is_between_quotes(fresh->line, i))
		{
			printf("minishell: syntax error near unexpected token `%c'\n", fresh->line[i]);
			return (1);
		}	
		i++;
	}
	return (0);
}
