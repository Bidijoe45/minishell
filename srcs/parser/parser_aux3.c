/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:41:40 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/19 10:49:52 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

int	extract_files_count_files(char *command)
{
	int	i;
	int	files;

	i = 0;
	files = 0;
	while (command[i] != '\0')
	{
		if ((command[i] == '>' || command[i] == '<')
			&& !is_between_quotes(command, i))
		{
			if (command[i + 1] == '>')
				i++;
			files++;
		}
		i++;
	}
	return (files);
}

void	extract_double_redirect(t_extract_files *extract, char *command,
	char **command_rpl)
{
	extract->redirect = extract->i;
	extract->i += 2;
	while (command[extract->i] == ' ')
		extract->i++;
	extract->pos = extract->i;
	while (command[extract->i] != '\0')
	{
		if ((command[extract->i] == ' ' || command[extract->i] == '<'
				|| command[extract->i] == '>')
			&& !is_between_quotes(command, extract->i))
			break ;
		extract->i++;
	}
	extract->file = malloc(sizeof(t_file));
	extract->file->file_name = ft_substr(command, extract->pos,
			extract->i - extract->pos);
	extract->file->type = APPEND;
	extract->files[extract->j] = extract->file;
	extract->tmp = *command_rpl;
	extract->key = ft_substr(command, extract->redirect, extract->i
			- extract->redirect);
	*command_rpl = ft_replace(extract->tmp, extract->key, "", 1);
	free(extract->key);
	free(extract->tmp);
	extract->j++;
}

void	extract_simple_redirect_aux(t_extract_files *extract, char *command,
char **command_rpl)
{
	while (command[extract->i] != '\0')
	{
		if ((command[extract->i] == ' ' || command[extract->i] == '<'
				|| command[extract->i] == '>')
			&& !is_between_quotes(command, extract->i))
			break ;
		extract->i++;
	}
}

void	extract_simple_redirect(t_extract_files *extract, char *command,
	char **command_rpl)
{
	extract->redirect = extract->i;
	extract->i++;
	while (command[extract->i] == ' ')
		extract->i++;
	extract->pos = extract->i;
	extract_simple_redirect_aux(extract, command, command_rpl);
	extract->file = malloc(sizeof(t_file));
	extract->file->file_name = ft_substr(command, extract->pos,
			extract->i - extract->pos);
	if (command[extract->redirect] == '>')
		extract->file->type = OUT;
	else if (command[extract->redirect] == '<')
		extract->file->type = IN;
	extract->files[extract->j] = extract->file;
	extract->tmp = *command_rpl;
	extract->key = ft_substr(command, extract->redirect, extract->i
			- extract->redirect);
	*command_rpl = ft_replace(extract->tmp, extract->key, "", 1);
	free(extract->key);
	free(extract->tmp);
	extract->j++;
}

t_file	**extract_files(char *command, char **command_rpl)
{
	t_extract_files	extract;

	extract.pos = 0;
	extract.j = 0;
	*command_rpl = ft_strdup(command);
	extract.n_files = extract_files_count_files(command);
	extract.files = malloc(sizeof(t_file *) * extract.n_files + 1);
	extract.files[extract.n_files] = NULL;
	extract.i = 0;
	while (command[extract.i] != '\0')
	{
		while (command[extract.i] == ' ')
			extract.i++;
		if (command[extract.i] == '>' && command[extract.i + 1] == '>'
			&& !is_between_quotes(command, extract.i))
			extract_double_redirect(&extract, command, command_rpl);
		else if ((command[extract.i] == '>' || command[extract.i] == '<')
			&& !is_between_quotes(command, extract.i))
			extract_simple_redirect(&extract, command, command_rpl);
		else
			extract.i++;
	}
	return (extract.files);
}
