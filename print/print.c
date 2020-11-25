/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:31:58 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/25 11:44:17 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

void    ft_print_color(char *color, char *str)
{
    write(1, "\033", 1);
    write(1, color, ft_strlen(color));
    write(1, str, ft_strlen(str));
}