/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/12/03 13:58:12 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

void    ft_export(t_fresh *fresh)
{
	char	**var;
	char	*var_name;
	char	*tmp_env;
	int		env_vars;
	int		i;

	var = ft_split(fresh->line, ' ');
	if (var[1])
		var_name = ft_strdup(var[1]);
	free(var[0]);
	free(var[1]);
	free(var);

	if (fresh->env_mod == 1)
	{
		
	}

	env_vars = 0;
	while(fresh->env[env_vars])
		env_vars++;
	printf("%d \n", env_vars);
}