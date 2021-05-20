/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/05/13 13:20:41 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"

void	print_list(t_list *list)
{
	t_list		*i;
	t_variable	*var;

	i = list;
	while (i)
	{
		var = (t_variable *)i->content;
		if (var->value)
			printf("declare -x %s=\"%s\"\n", var->key, var->value);
		else
			printf("declare -x %s\n", var->key);
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
			if (((t_variable *)elem->content)->key[0]
				> ((t_variable *)elem->next->content)->key[0])
			{
				swap(elem, elem->next);
				swapped = 1;
			}
			elem = elem->next;
		}
		next_elem = elem;
	}
}

int	validate_variable(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_command *command, t_fresh *fresh)
{
	t_export	export;

	export.key = NULL;
	export.value = NULL;
	if (!*command->args)
	{
		sort_list(fresh->env);
		print_list(fresh->env);
		return (0);
	}
	if (command->args[0][0] == '-')
	{
		printf("export: options not supported\n");
		return (1);
	}
	export.i = 0;
	return (export_while(command, fresh, &export));
}
