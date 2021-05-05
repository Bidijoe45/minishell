/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:02:12 by apavel            #+#    #+#             */
/*   Updated: 2021/05/05 11:28:03 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"

int	syntax_check_1(t_fresh *fresh)
{
	if (check_pipe_followed_by_another(fresh))
		return (1);
	if (check_semicolon_followed_by_another(fresh))
		return (1);
	if (check_semicolon_at_start(fresh))
		return (1);
	if (check_greater_at_start(fresh))
		return (1);
	if (check_more_than_three_greater_in_a_row(fresh))
		return (1);
	if (check_if_pipe_at_end(fresh))
		return (1);
	if (check_if_pipe_after_semicolon(fresh))
		return (1);
	return (0);
}

int	syntax_check_2(t_fresh *fresh)
{
	if (check_if_pipe_before_semicolon(fresh))
		return (1);
	if (check_lower_before_semicolon(fresh))
		return (1);
	if (check_greater_before_semicolon(fresh))
		return (1);
	if (check_greater_lower_before_pipe(fresh))
		return (1);
	if (check_pipe_before_greater_lower(fresh))
		return (1);
	if (check_lower_in_a_row(fresh))
		return (1);
	if (check_lower_greater_at_end(fresh))
		return (1);
	if (check_pipe_at_start(fresh))
		return (1);
	return (0);
}

int	syntax_checker(t_fresh *fresh)
{
	if (syntax_check_1(fresh))
		return (1);
	if (syntax_check_2(fresh))
		return (1);
	return (0);
}
