/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/12/21 12:18:08 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

int			count_vars(char *arg)
{
	int		i;
	int		count;
	int		dq;
	int		sq;
	char	*tmp;

	i = 0;
	dq = 0;
	sq = 0;
	count = 0;
	tmp = ft_strtrim(arg, " \n");
	if (ft_strlen(tmp) == 0)
		return (count);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '"' && sq == 0)
			dq = !dq;
		if (tmp[i] == '\'' && dq == 0)
			sq = !sq;
		if (tmp[i] == ' ' && dq == 0 && sq==0 && tmp[i - 1] != ' ')
			count++;
		i++;
	}

	return (count + 1);
}

void		ft_export(t_fresh *fresh, char *arg)
{
	int		i;
	int		pos;
	char	**splt_arg;
	int		dq;
	int		sq;

	if (ft_strlen(arg) == 0)
	{
		//TODO: imprimir export
	}

	printf("ret: %d\n", count_vars(arg));
	return ;

	i = 0;
	dq = 0;
	sq = 0;
	pos = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' && sq == 0)
			dq = !dq;
		if (arg[i] == '\'' && dq == 0)
			sq = !sq;

		if (arg[i] == '=' && dq == 0 && sq==0)
		{
			
			pos = i + 1;
			i++;
		}
		else
			i++;
	}

}