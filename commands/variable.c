/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:21:03 by apavel            #+#    #+#             */
/*   Updated: 2020/12/03 12:27:06 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

int		ft_is_variable(char *command)
{
	if (ft_strchr(command, '='))
		return (1);
	return (0);	
}

void	ft_set_variable(t_fresh *fresh, char *command)
{
	char **vars;
	t_variable *var;

	vars = ft_split(command, '=');
	var = malloc(sizeof(t_variable));
	var->key = vars[0];
	var->value = vars[1];
	if (!fresh->lst_variables)
		fresh->lst_variables = ft_lstnew(var);
	else
		ft_lstadd_back(&fresh->lst_variables, ft_lstnew(var));
}

char	*ft_get_variable(t_fresh *fresh, char *key)
{
	t_list		*lst;
	t_variable	*element;
	
	lst = fresh->lst_variables;
	if (lst)
	{
		while (lst)
		{
			element = (t_variable *)lst->content;
			if (!ft_strncmp(element->key, key, ft_strlen(key)))
				return (element->value);
			lst = lst->next;
		}
	}
	return NULL;
}