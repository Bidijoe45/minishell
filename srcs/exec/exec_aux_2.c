/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:02:23 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/29 19:03:04 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

char	**ft_list_to_chararr(t_list *list)
{
	char	**arr;
	t_list	*tmp;
	char	*tmp2;
	int		size;
	int		i;

	size = ft_lstsize(list);
	i = 0;
	arr = ft_malloc(sizeof(char *) * (size + 1));
	tmp = list;
	while (tmp)
	{
		if (((t_variable *)tmp->content)->key == NULL
			|| ((t_variable *)tmp->content)->value == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		tmp2 = ft_strjoin(((t_variable *)tmp->content)->key, "=");
		arr[i] = ft_strjoin(tmp2, ((t_variable *)tmp->content)->value);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_create_argv(t_command *command, char *path)
{
	char	**argv;
	int		argc;
	int		i;
	int		j;

	argc = 0;
	i = 1;
	j = 0;
	while (command->args[argc])
		argc++;
	if (argc == 0)
		return (ft_split(path, ' '));
	if (path == NULL)
		return (NULL);
	argv = ft_malloc(sizeof(char *) * (argc + 2));
	argv[0] = path;
	while (j < argc)
	{
		argv[i] = command->args[j];
		i++;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*create_path(char *path, char *cmd)
{
	char	*tmp;

	if (path == NULL)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, "/");
	free(tmp);
	tmp = path;
	path = ft_strjoin(path, cmd);
	free(tmp);
	return (path);
}

void	ft_replace_exit_status(t_fresh *fresh, t_command *command)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp = ft_itoa(fresh->cmd_return);
	tmp2 = command->cmd;
	command->cmd = ft_replace2(command->cmd, "$?", tmp, 0);
	free(tmp2);
	while (command->args[i])
	{
		tmp2 = command->args[i];
		command->args[i] = ft_replace2(command->args[i], "$?", tmp, 0);
		free(tmp2);
		i++;
	}
	i = -1;
	while (command->files[++i])
	{
		tmp2 = command->files[i]->file_name;
		command->files[i]->file_name
			= ft_replace2(command->files[i]->file_name, "$?", tmp, 0);
		free(tmp2);
	}
	free(tmp);
}

int	check_paths(char **r_path, char **paths, t_command *command)
{
	int				i;
	char			*path;
	struct stat		f_stat;
	int				status;

	i = 0;
	while (paths[i])
	{
		path = create_path(paths[i], command->cmd);
		status = lstat(path, &f_stat);
		if (!status && S_ISREG(f_stat.st_mode))
		{
			free(paths);
			*r_path = path;
			return (1);
		}
		i++;
	}
	*r_path = NULL;
	return (0);
}
