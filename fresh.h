/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:59:53 by apavel            #+#    #+#             */
/*   Updated: 2020/11/25 11:45:29 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AATANIC_H
# define AATANIC_H

# define NAME "fresh"
# define ART "███████╗██████╗ ███████╗███████╗██╗  ██╗\n██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n█████╗  ██████╔╝█████╗  ███████╗███████║\n██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n██║     ██║  ██║███████╗███████║██║  ██║\n╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n                                        \n"

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./print/colors.h"
# include <unistd.h>

typedef struct  s_fresh
{
	char        **env;
	char        *user;
	char		*line;
}               t_fresh;


#endif