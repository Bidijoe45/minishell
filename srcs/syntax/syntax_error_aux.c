/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:44:07 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/07 11:42:24 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/parser.h"

int	aux_1(t_fresh *fresh, int i)
{
	if (fresh->line[i] == '<')
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			fresh->line[i]);
		return (1);
	}
	return (0);
}

int	aux_2(t_fresh *fresh, int i, int rd)
{
	if (rd >= 3)
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			fresh->line[i]);
		return (1);
	}
	return (0);
}
