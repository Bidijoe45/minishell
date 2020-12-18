/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:13:11 by alvrodri          #+#    #+#             */
/*   Updated: 2020/12/18 11:32:12 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"

void	ft_echo(char *cmd, t_fresh *fresh)
{
	int		i;
	int		trail;
	char	*str;
	char	*tmp;

	i = 0;
	trail = 1;
	str = ft_substr(cmd, 4, ft_strlen(cmd) - 5);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		trail = 0;
	if (!trail)
	{
		tmp = str;
		str = ft_substr(&str[i + 2], 0, ft_strlen(&str[i + 2]));
		free(tmp);
	}
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (trail)
		write(1, "\n", 1);
	free(str);
}