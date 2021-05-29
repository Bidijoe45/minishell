/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:59:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/29 19:03:36 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/command.h"
#include "../../includes/print.h"
#include "../../includes/parser.h"
#include "../../includes/list.h"

int	ft_is_builtin(t_fresh *fresh, t_command *command)
{
	char	*name;

	(void)fresh;
	name = command->cmd;
	if (!ft_strncmp(name, "echo\0", 5))
		return (1);
	else if (!ft_strncmp(name, "cd\0", 3))
		return (1);
	else if (!ft_strncmp(name, "export\0", 7))
		return (1);
	else if (!ft_strncmp(name, "env\0", 4))
		return (1);
	else if (!ft_strncmp(name, "unset\0", 6))
		return (1);
	else if (!ft_strncmp(name, "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(name, "exit\0", 5))
		return (1);
	return (0);
}

void	ft_execute_builtin(t_command *command, t_fresh *fresh)
{
	char	*name;

	(void)fresh;
	name = command->cmd;
	if (!ft_strncmp(name, "echo\0", 5))
		fresh->cmd_return = ft_echo(command, fresh);
	else if (!ft_strncmp(name, "cd\0", 3))
		fresh->cmd_return = ft_cd(command, fresh);
	else if (!ft_strncmp(name, "export\0", 7))
		fresh->cmd_return = ft_export(command, fresh);
	else if (!ft_strncmp(name, "env\0", 4))
		fresh->cmd_return = ft_env(command, fresh);
	else if (!ft_strncmp(name, "unset\0", 6))
		fresh->cmd_return = ft_unset(command, fresh);
	else if (!ft_strncmp(name, "pwd\0", 4))
		fresh->cmd_return = ft_pwd(command, fresh);
	else if (!ft_strncmp(name, "exit\0", 5))
		fresh->cmd_return = ft_exit(command, fresh);
	else
		return ;
}

void	ft_exec_bin_child(t_fresh *fresh, t_command *command)
{
	char	*path;
	char	**argv;
	char	**chararr;

	path = ft_check_if_valid(fresh, command);
	argv = ft_create_argv(command, path);
	chararr = ft_list_to_chararr(fresh->env);
	if (path)
		execve(path, argv, chararr);
	else
	{
		argv = NULL;
		free(path);
		path = NULL;
		dup2(fresh->fd_out, 1);
		if (ft_strlen(command->cmd) == 0)
			exit(0);
		printf("%s: command not found\n", command->cmd);
		exit(127);
	}
	argv = NULL;
	exit(errno);
}

int	ft_exec_bin(t_fresh *fresh, t_command *command, int infork)
{
	int		status;

	(void)infork;
	status = 0;
	fresh->pid = fork();
	if (fresh->pid == 0)
		ft_exec_bin_child(fresh, command);
	else
		wait(&status);
	fresh->cmd_return = status >> 8;
	return (status);
}

char	*ft_check_if_valid(t_fresh *fresh, t_command *command)
{
	struct stat		f_stat;
	char			*path;
	char			**paths;

	path = NULL;
	if (variable_get(fresh->env, "PATH") == NULL)
		return (NULL);
	paths = ft_split(variable_get(fresh->env, "PATH")->value, ':');
	if (check_paths(&path, paths, command))
		return (path);
	if (path)
		free(path);
	path = ft_strtrim(command->cmd, "\n");
	if (path[0] != '.' && path[0] != '/')
		return (NULL);
	if (!lstat(path, &f_stat) && !S_ISDIR(f_stat.st_mode)
		&& f_stat.st_mode & S_IXUSR)
		return (path);
	free(path);
	free(paths);
	return (NULL);
}
