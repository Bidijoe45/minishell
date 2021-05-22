/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:26:23 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/22 12:40:09 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"

/*
 * CTRL + C outside fork
 */

void	global_sigint(int code)
{
	(void)code;
	printf("\b\b  \n");
	ft_print_input(NULL);
}

/*
 * CTRL + C inside fork
 */

void	fork_sigint(int code)
{
	(void)code;
	printf("\n");
}

/*
 * CTRL + \ outside fork
 */

void	global_sigquit(int code)
{
	(void)code;
	write(1, "\b\b  \b\b", 6);
	return ;
}

/*
 * CTRL + \ inside fork
 */

void	fork_sigquit(int code)
{
	(void)code;
	printf("Quit: %d\n", code);
}
