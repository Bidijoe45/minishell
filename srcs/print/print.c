/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:31:58 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/31 10:43:35 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"

void	ft_print_color(char *color, char *str, int fd)
{
	ft_putstr_fd("\033", fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
}

void	ft_print_input(t_fresh *fresh)
{
	(void)fresh;
	ft_print_color(BOLD_GREEN, "fresh", 2);
	ft_print_color(GREEN, " > ", 2);
	ft_print_color(RESET, "", 2);
}

void	ft_print_header(t_fresh *fresh)
{
	(void)fresh;
	ft_print_color(BOLD_GREEN, ART, 2);
	ft_print_color(BOLD_GREEN, "fresh", 2);
	ft_print_color(GREEN, " > ", 2);
	ft_print_color(RESET, "", 2);
}

void	ft_print_error(t_fresh *fresh, char *error_str)
{
	(void)fresh;
	ft_print_color(RESET, "", 2);
	ft_print_color(RED, "Error: ", 2);
	ft_print_color(RESET, error_str, 2);
	ft_print_color(RESET, "\n", 2);
}
