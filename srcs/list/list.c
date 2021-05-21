/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 12:55:25 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/21 12:45:53 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

t_list	*list_new_element(void *content)
{
	t_list	*list;

	list = ft_malloc(sizeof(t_list));
	list->content = content;
	list->next = NULL;
	return (list);
}

void	list_add_back(t_list *list, t_list *new_elem)
{
	t_list	*elem;

	if (!list)
		return ;
	elem = list;
	while (elem)
	{
		if (elem->next == NULL)
		{
			elem->next = new_elem;
			return ;
		}
		else
			elem = elem->next;
	}
}

void	ft_load_env_vars(t_fresh *fresh, char **envp)
{
	char		**split_var;
	int			i;
	t_variable	*var;

	i = 0;
	while (envp[i])
	{
		split_var = ft_split(envp[i], '=');
		var = variable_new(ft_strdup(split_var[0]), ft_strdup(split_var[1]));
		if (fresh->env)
			list_add_back(fresh->env, list_new_element(var));
		else
			fresh->env = list_new_element(var);
		i++;
		ft_free_split(split_var);
	}
	if (variable_get(fresh->env, "OLDPWD"))
		variable_mod(fresh->env, "OLDPWD", NULL);
}
