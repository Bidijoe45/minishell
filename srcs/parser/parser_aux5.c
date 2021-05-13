/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:43:50 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 17:45:52 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

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
