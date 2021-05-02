/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:21:47 by apavel            #+#    #+#             */
/*   Updated: 2020/03/10 15:34:42 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_flags
{
	int			printed;
	short		f_minus;
	short		f_zero;
	short		f_width;
	int			n_width;
	short		f_precision;
	int			n_precision;
	char		type;
	va_list		args;
}				t_flags;

int				ft_printf(const char *format, ...);
void			ft_start_flags(t_flags *flags, va_list args);
void			ft_restart_flags(t_flags *flags);
int				ft_parse(t_flags *flags, va_list args, const char *format);
void			ft_parse_width(t_flags *flags, const char *format);
int				ft_display(t_flags *flags, char type);
int				ft_display_c(t_flags *flags);
int				ft_display_s(t_flags *flags);
int				ft_display_int(t_flags *flags);
int				ft_display_u(t_flags *flags);
int				ft_display_x(t_flags *flags);
int				ft_display_p(t_flags *flags);
void			ft_display_percentage(t_flags *flags);
char			*ft_itoa_u(long n);
char			*ft_itox(unsigned long n, char type);

#endif
