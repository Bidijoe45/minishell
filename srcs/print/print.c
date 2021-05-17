/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:31:58 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/17 10:54:01 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"

void	ft_print_color(char *color, char *str)
{
	ft_putstr_fd("\033", 1);
	ft_putstr_fd(color, 1);
	ft_putstr_fd(str, 1);
}

void	ft_print_input(t_fresh *fresh)
{
	ft_print_color(BOLD_GREEN, "fresh");
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}

void	ft_print_header(t_fresh *fresh)
{
	ft_print_color(BOLD_GREEN, ART);
	ft_print_color(BOLD_GREEN, "fresh");
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}

void	ft_print_error(t_fresh *fresh, char *error_str)
{
	ft_print_color(RESET, "");
	ft_print_color(RED, "Error: ");
	ft_print_color(RESET, error_str);
	ft_print_color(RESET, "\n");
}
