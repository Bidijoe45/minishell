/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:13:11 by alvrodri          #+#    #+#             */
/*   Updated: 2020/12/22 13:25:21 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

int		ft_set_trail(char *str)
{
	int i;
	int	trail;
	
	i = 0;
	if (str[i++] == '-')
	{
		while (str[i] == 'n')
		{
			trail = 0;
			i++;
		}
		if (str[i] != ' ' && str[i] != '\0')
			trail = 1;
	}
	return (trail);
}

void	ft_echo(char *cmd, t_fresh *fresh)
{
	int		i;
	int		trail;
	char	*str;
	char	*tmp;

	i = 0;
	trail = 1;
	if (cmd[4] != '\n' && cmd[4] != ' ')
		return ft_not_found(cmd);
	str = ft_substr(cmd, 4, ft_strlen(cmd) - 5);
	while (ft_isspace(str[i]))
		i++;
	trail = ft_set_trail(&str[i]);
	free(str);
}