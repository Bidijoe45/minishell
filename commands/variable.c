/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:21:03 by apavel            #+#    #+#             */
/*   Updated: 2020/12/15 12:46:40 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../fresh.h"
#include "command.h"

t_variable	*ft_new_variable(char *key, char *value)
{
	t_variable *var;

	var = malloc(sizeof(t_variable));
	var->key = key;
	var->value = value;
	return (var);
}

t_variable	*ft_get_variable(t_list *variables, char *key)
{
	t_list	*elem;
	t_variable	*var;
	
	if (!variables)
		return (NULL);
	elem = variables;
	while (elem)
	{
		var = elem->content;
		if (!ft_strncmp(var->key, key, ft_strlen(key)))
			return (var);
		elem = elem->next;
	}
	return (NULL);
}

void	ft_set_variable(t_list *variables, t_variable *var)
{
	t_variable	*ret_var;
	t_list		*elem;

	if (!variables)
		return ;
	if ((ret_var = ft_get_variable(variables, var->key)))
		ret_var->value = var->value;
	elem = variables;
	while (elem)
	{
		elem = elem->next;
		if (elem == NULL)
		{
			elem = ft_lstnew(var);
			return ;
		}
	}
}