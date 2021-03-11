/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/12/20 10:51:46 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "../print/print.h"
#include "command.h"

int    ft_cd(char *cmd, t_fresh *fresh)
{
    char    **argv;
    char    *tmp;
    int     ret;

    argv = ft_split(cmd, ' ');
    if (argv[1] == NULL)
    {
        ret = chdir(variable_get(fresh->env, "HOME")->value);
        free(argv);
        return (ret);
    }
	if (argv[1][0] == '~')
	{
		tmp = argv[1];
		argv[1] = ft_strjoin(variable_get(fresh->env, "HOME")->value, &argv[1][1]);
		free(tmp);
	}
	tmp = argv[1];
    ret = chdir((argv[1] = ft_strtrim(tmp, "\n")));
	free(tmp);
    if (ret == -1)
        ft_print_error(fresh, "Not found");
    free(argv);
    return (ret);
}