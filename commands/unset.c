/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/03/15 11:39:02 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "./command.h"

void	free_var(t_list *list)
{
	t_variable *var;

	var = ((t_variable *)list->content);
	free(var->key);
	free(var->value);
	free(var);
	free(list);
}

void	remove_var(t_fresh *fresh, char *key)
{
	t_list		*elem;
	t_list		*next;
	t_list		*tmp;
	t_variable	*var;

	elem = fresh->env;
	if (!ft_strncmp(((t_variable *)elem->content)->key, key, ft_strlen(key)))
	{
		tmp = elem;
		fresh->env = elem->next;
		free_var(elem);
		return ;
	}
	while (elem)
	{
		next = elem->next;
		if (!next)
			break ;
		if (!ft_strncmp(((t_variable *)next->content)->key, key, ft_strlen(key)))
		{
			elem->next = next->next;
			free_var(next);
		}
		elem = elem->next;
	}
}

int		ft_unset(t_fresh *fresh, t_command *command)
{
	int		i;
	char	**vars;

	i = 0;
	vars = ft_split(command->arg, ' ');
	while (vars[i])
	{
		remove_var(fresh, ft_strtrim(vars[i], "\n"));
		i++;
	}
	return (1);
}
