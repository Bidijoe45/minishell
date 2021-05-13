/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:20:24 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 13:22:50 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"

void	export_aux(t_export *export, t_command *command, t_fresh *fresh)
{
	if (ft_strchr(command->args[export->i], '='))
	{
		export->key = ft_substr(command->args[export->i], 0,
				ft_strchr(command->args[export->i], '=')
				- command->args[export->i]);
		export->value = ft_strdup(ft_strchr(command->args[export->i], '=') + 1);
	}
	else
		export->key = ft_strdup(command->args[export->i]);
	export->key = ft_replace(export->key, "\"", "", 0);
	if (export->value)
	{
		export->tmp = export->value;
		export->value = ft_strtrim(export->value, "\"");
		free(export->tmp);
		export->tmp = export->value;
		export->value = ft_strtrim(export->value, "'");
		free(export->tmp);
	}
}

void	export_aux2(t_export *export, t_fresh *fresh)
{
	if (!export->value)
	{
		if (!variable_get(fresh->env, export->key))
			variable_set(&fresh->env, export->key, NULL);
	}
	else
	{
		if (variable_get(fresh->env, export->key))
		{
			variable_mod(fresh->env, export->key, export->value);
			free(export->key);
		}
		else
			variable_set(&fresh->env, export->key, export->value);
	}
}

int	export_while(t_command *command, t_fresh *fresh, t_export *export)
{
	while (command->args[export->i])
	{
		export_aux(export, command, fresh);
		if (!validate_variable(export->key))
		{
			if (export->value)
				printf("export: `%s=%s': not a valid identifier\n",
					export->key, export->value);
			else
				printf("export: `%s': not a valid identifier\n", export->key);
			return (1);
		}
		export_aux2(export, fresh);
		export->value = NULL;
		export->key = NULL;
		export->i++;
	}
	return (0);
}
