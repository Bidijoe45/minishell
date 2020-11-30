/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:28:30 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/30 11:18:59 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct	s_flags
{
	int			width;
	int			precision;
	int			minus;
	int			zero;
	int			written;
}				t_flags;

int				ft_printf(const char *str, ...);
int				ft_get_spaces(char *str, t_flags *flags);
int				ft_get_nbr(const char *str, int *i);
int				ft_get_length(int nbr);
int				ft_print_blank(int len, int zero);
int				ft_enable_flags(const char *str, t_flags *flags, va_list args);
void			ft_print_specific(char type, va_list list, t_flags *flags);
void			ft_print_char(char c, t_flags *flags);
void			ft_print_str(va_list list, t_flags *flags);
void			ft_print_int(int nbr, t_flags *flags);
void			ft_print_uint(unsigned int nbr, t_flags *flags);
void			ft_print_pointer(unsigned long address, t_flags *flags);
void			ft_print_x_low(unsigned int nbr, t_flags *flags);
void			ft_print_x_up(unsigned int nbr, t_flags *flags);

#endif
