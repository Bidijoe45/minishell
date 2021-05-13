/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:42:48 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/13 17:45:55 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

int	extract_cmd_count_greater_lower(char *command, int i)
{	
	i++;
	while (command[i] == ' ')
		i++;
	while (command[i] != ' ' && command[i] != '<' && command[i] != '>'
		&& command[i] != '\0')
		i++;
	return (i);
}

int	extract_cmd_count_space_greater_lower(char *command, int i)
{
	while ((command[i] != ' ' && command[i] != '>' && command[i] != '<'
			&& command[i] != '\0' && command[i] != '\n')
		|| (is_between_quotes(command, i) && command[i] != '\0'))
		i++;
	return (i);
}

char	*extract_cmd(char *command, char **command_rpl)
{
	int		i;
	int		pos;
	char	*key;

	i = 0;
	pos = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if ((command[i] == '>' || command[i] == '<')
			&& !is_between_quotes(command, i))
			i = extract_cmd_count_greater_lower(command, i);
		else
		{
			pos = i;
			i = extract_cmd_count_space_greater_lower(command, i);
			key = ft_substr(command, pos, i - pos);
			*command_rpl = ft_replace(command, key, "", 1);
			free(key);
			return (ft_substr(command, pos, i - pos));
		}
	}
	*command_rpl = ft_strdup(command);
	return (ft_strdup(""));
}

int	check_chars(char c)
{
	return (c == '>' || c == '<');
}

int	check_invalid_redirections(char **cmds)
{
	int		l;
	int		i;
	char	*cmd;

	i = 0;
	while (cmds[i])
	{
		cmd = ft_strtrim(cmds[i], " ");
		l = ft_strlen(cmd);
		if ((check_chars(cmd[0] && cmd[0] == '|') || check_chars(cmd[l - 1]))
			&& (!is_between_quotes(cmd, 0) && !is_between_quotes(cmd, l - 1)))
		{
			free(cmd);
			return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}
