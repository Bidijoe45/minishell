/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2020/11/30 11:56:14 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "../print/print.h"

void    ft_exit(char *exit_code)
{
    int i;

    i = 0;
    while (exit_code && exit_code[i++])
    {
        if (!ft_isdigit(exit_code[i]))
            exit(255);
    }
    ft_print_color(BOLD_GREEN, "See you soon!\n\n");
    exit(!*exit_code ? 0 : ft_atoi(exit_code));
}