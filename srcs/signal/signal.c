/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:26:23 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 11:29:10 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"

/*
 * CTRL + C outside fork
 */

void	global_sigint(int code)
{
	printf("\b\b  \n");
	ft_print_input(NULL);
}

/*
 * CTRL + C inside fork
 */

void	fork_sigint(int code)
{
	signal(SIGINT, fork_sigint);
	printf("\n");
}

/*
 * CTRL + \ outside fork
 */

void	global_sigquit(int code)
{
	return ;
}

/*
 * CTRL + \ inside fork
 */

void	fork_sigquit(int code)
{
	signal(SIGQUIT, fork_sigquit);
	printf("Quit: %d\n", code);
}
