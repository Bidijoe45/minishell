/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:38:14 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/30 12:52:29 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

#include "../fresh.h"

#define RED "[0;31m"
#define BOLD_RED "[1;31m"
#define GREEN "[0;32m"
#define BOLD_GREEN "[1;32m"
#define YELLOW "[0;33m"
#define BLUE "[0;34m"
#define BOLD_BLUE "[1;34m"
#define MAGENTA "[0;35m"
#define BOLD_MAGENTA "[1;35m"
#define CYAN "[0;36m"
#define BOLD_CYAN "[1;36m"
#define RESET "[0m"

void    ft_print_color(char *colour, char *str);
void	ft_print_header(t_fresh *fresh);
void	ft_print_error(t_fresh *fresh, char *error_str);
void	ft_print_input(t_fresh *fresh);
void    ft_not_found(char *cmd);

#endif