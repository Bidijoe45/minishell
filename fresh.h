/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2020/12/03 13:54:40 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AATANIC_H
# define AATANIC_H

# define NAME "fresh"
# define ART "███████╗██████╗ ███████╗███████╗██╗  ██╗\n██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n█████╗  ██████╔╝█████╗  ███████╗███████║\n██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n██║     ██║  ██║███████╗███████║██║  ██║\n╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n                                        \n"

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf_utils.h"
# include "./print/colors.h"
# include <sys/errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct  s_fresh
{
	char        **env;
	int			env_mod;
	char        *user;
	char		*line;
	t_list		*lst_variables;
}               t_fresh;


#endif