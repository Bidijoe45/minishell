/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/03/15 09:20:02 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "../print/print.h"
#include "command.h"

static	void	free_bidimensional(char **mem)
{
	int i;

	i = 0;
	while (mem[i] != NULL)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

int	ft_cd(t_fresh *fresh, t_command *command)
{
	char	**argv;
	char	*tmp;
	int		ret;

	argv = ft_split(command->arg, ' ');
	if (argv[0] == NULL || argv[0][0] == '\n')
	{
		ret = chdir(variable_get(fresh->env, "HOME")->value);
		variable_mod(fresh->env, "PWD", variable_get(fresh->env, "HOME")->value);
		free_bidimensional(argv);
		return (ret);
	}
	tmp = ft_strtrim(argv[0], "\n");
	ret = chdir(tmp);
	variable_mod(fresh->env, "PWD", ft_strdup(tmp));
	if (ret == -1)
		ft_print_error(fresh, "Not found");
	free_bidimensional(argv);
	free(tmp);
	return (ret);
}
