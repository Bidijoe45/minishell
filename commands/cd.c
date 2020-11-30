/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/11/30 12:51:27 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

void    ft_cd(char *cmd, t_fresh *fresh)
{
    char    **argv;
    int     ret;

    argv = ft_split(cmd, ' ');
    ret = chdir(argv[1]);
    if (ret == -1)
        ft_printf("%sError: %s%s\n", RED, RESET, strerror(errno));
}