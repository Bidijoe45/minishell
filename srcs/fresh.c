/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
/*   Updated: 2021/05/10 14:58:09 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fresh.h"
#include "../includes/command.h"
#include "../includes/print.h"
#include "../includes/parser.h"
#include "../includes/list.h"

void	ft_initialize(t_fresh *fresh)
{
	fresh->cmd_return = 0;
	fresh->env = NULL;
	fresh->line = NULL;
	fresh->local_vars = NULL;
	fresh->user = NULL;
	fresh->commands = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_fresh	fresh;

	(void)argv;
	(void)argc;
	ft_initialize(&fresh);
	ft_load_env_vars(&fresh, envp);
	ft_print_header(&fresh);
	while (1)
	{
		signal(SIGINT, global_sigint);
		signal(SIGQUIT, global_sigquit);
		read_line(&fresh);
		signal(SIGINT, fork_sigint);
		signal(SIGQUIT, fork_sigquit);
		if (!ft_valid_multiline(&fresh))
			ft_putstr_fd("Multiline line commands are not supported.\n", 1);
		else
			ft_parse_line(&fresh);
		free(fresh.line);
		fresh.line = NULL;
		ft_execute_commands(&fresh);
		ft_free_commands(&fresh);
		ft_print_input(&fresh);
	}
}
