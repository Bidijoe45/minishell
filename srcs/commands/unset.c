/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/05/03 12:00:04 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"

void	variable_unset(t_fresh *fresh, char *key, t_list *list, t_variable *tmp)
{
	t_list		*prev;
	t_variable	*var;

	var = variable_get(fresh->env, key);
	if (!var)
		return ;
	while (list)
	{
		tmp = (t_variable *)list->content;
		if (ft_strlen(tmp->key) == ft_strlen(var->key)
			&& !ft_strncmp(tmp->key, var->key, ft_strlen(var->key)))
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			if (list == fresh->env)
				fresh->env = list->next;
			else
				prev->next = list->next;
			free(list);
			break ;
		}
		prev = list;
		list = list->next;
	}
}

static	int	validate_variable(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_command *command, t_fresh *fresh)
{
	int	i;

	if (command->args[0])
	{
		if (command->args[0][0] == '-')
		{
			if (!command->args[0][1])
				printf("unset: `%s': not a valid identifier\n",
					command->args[0]);
			else
				printf("unset: %s: invalid option\n", command->args[0]);
			return (1);
		}
	}
	i = 0;
	while (command->args[i])
	{
		if (!(validate_variable(command->args[i])))
			printf("unset: `%s': not a valid identifier\n", command->args[i]);
		else
			variable_unset(fresh, command->args[i], fresh->env, NULL);
		i++;
	}
	return (0);
}
