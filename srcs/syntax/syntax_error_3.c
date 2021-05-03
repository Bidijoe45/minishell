/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:41:38 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/03 13:22:03 by alvrodri         ###   ########.fr       */
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
