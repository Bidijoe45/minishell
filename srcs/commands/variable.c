/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:21:03 by apavel            #+#    #+#             */
/*   Updated: 2021/05/19 11:04:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/list.h"

t_variable	*variable_new(char *key, char *value)
{
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	var->key = key;
	var->value = value;
	return (var);
}

t_variable	*variable_get(t_list *variables, char *key)
{
	t_list		*elem;
	t_variable	*var;

	if (!variables)
		return (NULL);
	elem = variables;
	while (elem)
	{
		var = elem->content;
		if (!ft_strncmp(var->key, key, ft_strlen(key))
			&& ft_strlen(var->key) == ft_strlen(key))
			return (var);
		elem = elem->next;
	}
	return (NULL);
}

void	variable_set(t_list **variables, char *key, char *value)
{
	t_list		*new_elem;
	t_variable	*var;

	if (!*variables)
		return ;
	var = variable_get(*variables, key);
	if (var != NULL)
	{
		var->value = value;
		return ;
	}
	if (*variables)
	{
		new_elem = list_new_element(variable_new(key, value));
		list_add_back(*variables, new_elem);
	}
	else
		*variables = list_new_element(variable_new(key, value));
}

void	variable_mod(t_list *variables, char *key, char *value)
{
	t_list		*elem;
	t_variable	*var;

	if (!variables)
		return ;
	elem = variables;
	while (elem)
	{
		var = elem->content;
		if (!strncmp(var->key, key, ft_strlen(var->key)))
		{
			free(var->value);
			var->value = value;
		}
		elem = elem->next;
	}
}
