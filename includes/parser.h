/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:09:53 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 17:48:44 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "./fresh.h"

void	sort_list(t_list *list);
void	print_list(t_list *list);
void	read_line(t_fresh *fresh);
int		ft_valid_multiline(t_fresh *fresh);
void	ft_parse_line(t_fresh *fres);

#endif
