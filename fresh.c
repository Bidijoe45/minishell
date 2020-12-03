/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
/*   Updated: 2020/11/23 14:15:00 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fresh.h"
#include "commands/command.h"
#include "utils/utils.h"

void	ft_print_header(t_fresh *fresh)
{
	ft_print_color(BOLD_GREEN, ART);
	ft_print_color(BOLD_GREEN, fresh->user);
	ft_print_color(GREEN, " > ");
	ft_print_color(RESET, "");
}

int		main(int argc, char **argv, char **envp, char **apple)
{
	t_fresh fresh;
	int		i;

	fresh.env = envp;
	fresh.env_mod = 0;
	fresh.user = ft_get_var(fresh, "USER");
	ft_print_header(&fresh);
	while ((i = get_next_line(0, &fresh.line)) > 0)
	{
		ft_parse_command(&fresh);
		free(fresh.line);
		ft_print_color(BOLD_GREEN, fresh.user);
		ft_print_color(GREEN, " > ");
		ft_print_color(RESET, "");
	}
}
