/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/03/16 10:27:23 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void	print_list(t_list *list)
 {
 	t_list	*i;
 	t_variable *var;

 	i = list;
 	while (i)
 	{
 		var = (t_variable *)i->content;
 		printf("declare -x %s=%s\n", var->key, var->value);
 		i = i->next;
 	}
 }

void	swap(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sort_list(t_list *list)
{
	t_list	*elem;
	t_list	*next_elem;
	int		swapped;
	int		 i;

	if (list == NULL)
		return ;
	swapped = 1;
	next_elem = NULL;
	while (swapped)
	{
		swapped = 0;
		elem = list;
		while (elem->next != next_elem)
		{
			if (((t_variable *)elem->content)->key[0] > ((t_variable *)elem->next->content)->key[0])
			{
				swap(elem, elem->next);
				swapped = 1;
			}
			elem = elem->next;
		}
		next_elem = elem;
	}
}

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
		sort_list(fresh->env);
		print_list(fresh->env);
		return ;
	}
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
