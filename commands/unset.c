/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/03/15 11:34:43 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "./command.h"

void	remove_var(t_fresh *fresh, char *key)
{
	t_list		*elem;
	t_list		*next;
	t_variable	*var;

	elem = fresh->env;
	if (!ft_strncmp(((t_variable *)elem->content)->key, key, ft_strlen(key)))
	{
		var = ((t_variable *)elem->content);
		free(var->key);
		free(var->value);
		free(var);
		fresh->env = elem->next;
		free(elem);
		return ;
	}
	while (elem)
	{
		next = elem->next;
		if (!next)
			break ;
		if (!ft_strncmp(((t_variable *)next->content)->key, key, ft_strlen(key)))
		{
			var = ((t_variable *)next->content);
			free(var->key);
			free(var->value);
			free(var);
			free(next);
			elem->next = next->next;
		}
		elem = elem->next;
	}
}

void	print_list(t_list *list)
{
	t_list	*i;
	t_variable *var;

	i = list;
	while (i)
	{
		var = (t_variable *)i->content;
		printf("%s=%s", var->key, var->value);
		i = i->next;
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
	//print_list(fresh->env);
	return (1);
}
