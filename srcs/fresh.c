/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
/*   Updated: 2021/05/03 12:18:18 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fresh.h"
#include "../includes/command.h"
#include "../includes/print.h"
#include "../includes/parser.h"
#include "../includes/list.h"

t_fresh	*fresh;

void	ft_initialize(t_fresh *fresh)
{
	fresh->cmd_return = 0;
	fresh->env = NULL;
	fresh->line = NULL;
	fresh->local_vars = NULL;
	fresh->user = NULL;
	fresh->commands = NULL;
}

void	ft_ctrl_c(int signum)
{
	if (!fresh->pid)
	{
		printf("\b\b  \n");
		ft_print_input(fresh);
	}
	fresh->pid = 0;
	return ;
}

void	ft_ctrl_backslash(int signum)
{
	return ;
}

void	ft_load_env_vars(t_fresh *fresh, char **envp)
{
	char		**split_var;
	int			i;
	t_variable	*var;

	i = 0;
	while (envp[i])
	{
		split_var = ft_split(envp[i], '=');
		var = variable_new(ft_strdup(split_var[0]), ft_strdup(split_var[1]));
		if (fresh->env)
			list_add_back(fresh->env, list_new_element(var));
		else
			fresh->env = list_new_element(var);
		i++;
		ft_free_split(split_var);
	}
	if (variable_get(fresh->env, "OLDPWD"))
		variable_mod(fresh->env, "OLDPWD", NULL);
}

void	ft_free_commands(t_fresh *fresh)
{
	t_list	*list_elem;
	int		i;

	list_elem = fresh->commands;
	while (list_elem)
	{
		t_command *cmd = (t_command *)list_elem->content;
		free(cmd->cmd);
		if (cmd->files)
		{
			i = 0;
			while (cmd->files[i])
			{
				free(cmd->files[i]->file_name);
				free(cmd->files[i]);
				i++;
			}
		}
		free(cmd->files);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
		}
		free(cmd->args);
		free(cmd);
		free(list_elem);
		list_elem = list_elem->next;
	}
	fresh->commands = NULL;
}

int	ft_listsize(t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_list_to_chararr(t_list *list)
{
	char	**arr;
	t_list	*tmp;
	char	*tmp2;
	int		size;
	int		i;

	size = ft_listsize(list);
	i = 0;
	arr = malloc(sizeof(char *) * (size + 1));
	tmp = list;
	while (tmp)
	{
		if (((t_variable *)tmp->content)->value != NULL)
		{
			tmp2 = ft_strjoin(((t_variable *)tmp->content)->key, "=");
			arr[i] = ft_strjoin(tmp2, ((t_variable *)tmp->content)->value);
			free(tmp2);
		}
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
	argv = malloc(sizeof(char *) * (argc + 2));
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

char	*ft_check_if_valid(t_fresh *fresh, t_command *command)
{
	struct	stat	f_stat;
	int				i;
	int				status;
	char			*path;
	char			**paths;

	i = 0;
	path = NULL;
	if (variable_get(fresh->env, "PATH") == NULL)
		return (NULL);
	paths = ft_split(variable_get(fresh->env, "PATH")->value, ':');
	while (paths[i])
	{
		path = create_path(paths[i], command->cmd);
		status = lstat(path, &f_stat);
		if (!status && S_ISREG(f_stat.st_mode))
		{
			free(paths);
			return (path);
		}
		i++;
	}
	if (path)
		free(path);
	path = ft_strtrim(command->cmd, "\n");
	if (path[0] != '.' && path[0] != '/')
		return (NULL);
	if (!lstat(path, &f_stat) && !S_ISDIR(f_stat.st_mode) && f_stat.st_mode & S_IXUSR)
		return (path);
	free(path);
	free(paths);
	return (NULL);
}

int		ft_exec_bin(t_fresh *fresh, t_command *command)
{
	int		pid;
	int		status;
	char	**argv;
	char	*path;
	char	**chararr;

	fresh->pid = fork();
	if (fresh->pid == 0)
	{
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
			printf("%s: command not found\n", command->cmd);
			exit(127);
		}
		argv = NULL;
		exit(errno);
	}
	else
	{
		wait(&status);
		fresh->pid = 0;
	}
	fresh->cmd_return = status >> 8; 
	return (status);
}

int	ft_is_builtin(t_fresh *fresh, t_command *command)
{
	char *name;

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
	char *name;

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

/*
 * No me deja hacer free en estos replace de abajo, weird right?
 * osea que no se si hay leaks o no, porque es como que command
 * no está alocado, pero whatever yqc.
 *
 * Por cierto, hay que hacer que si están entre ' ' no se haga
 * el replace... (pero aquí ya nos llegan los arguments sin ').
 * */
void	ft_replace_exit_status(t_fresh *fresh, t_command *command)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_itoa(fresh->cmd_return);
	command->cmd = ft_replace(command->cmd, "$?", tmp, 0);
	while (command->args[i])
	{
		command->args[i] = ft_replace(command->args[i], "$?", tmp, 0);
		i++;
	}
	i = 0;
	while (command->files[i])
	{
		command->files[i]->file_name
		= ft_replace(command->files[i]->file_name, "$?", tmp, 0);
		i++;
	}
	free(tmp);
}

void	ft_execute_commands(t_fresh *fresh)
{
	int			i;
	int			pid;
	t_list		*list_elem;
	t_file		*last_in;
	t_file		*last_out;
	t_command	*p_command;
	int			fd[2];	

	last_in = NULL;
	last_out = NULL;
	p_command = NULL;
	list_elem = fresh->commands;
	while (list_elem)
	{
		t_command *command = (t_command *)list_elem->content;
		i = 0;
		ft_replace_exit_status(fresh, command);
		if (command->write_to_pipe)
			pipe(fd);
		while (command->files[i])
		{
			if (command->files[i]->type == IN)
				last_in = command->files[i];
			else
			{
				if (last_out)
					close(last_out->fd);
				last_out = command->files[i];
				if (last_out->type == OUT)
					last_out->fd = open(last_out->file_name, O_RDWR | O_TRUNC | O_CREAT, 0700);
				else if (last_out->type == APPEND)
					last_out->fd = open(last_out->file_name, O_RDWR | O_APPEND | O_CREAT, 0700);
			}
			i++;
		}
		if (last_in != NULL)
		{
			last_in->fd = open(last_in->file_name, O_RDONLY);
			if (last_in->fd == -1)
			{
				fresh->cmd_return = 1;
				printf("%s: No such file or directory\n", last_in->file_name);
				return ;
			}
			fresh->fd_in = dup(0);
			dup2(last_in->fd, 0);
			if (last_out != NULL)
			{
				fresh->fd_out = dup(1);
				dup2(last_out->fd, 1);
			}
			if (ft_is_builtin(fresh, command))
				ft_execute_builtin(command, fresh);
			else
				ft_exec_bin(fresh, command);
			close(last_in->fd);
			dup2(fresh->fd_in, 0);
			if (last_out != NULL)
			{
				close(last_out->fd);
				dup2(fresh->fd_out, 1);
			}
		}
		else
		{
			fresh->fd_out = dup(1);
			if (last_out != NULL)
				dup2(last_out->fd, 1);
			if (!command->write_to_pipe && !command->read_from_pipe)
			{
				if (ft_is_builtin(fresh, command))
					ft_execute_builtin(command, fresh);
				else
					ft_exec_bin(fresh, command);
			}
			if (command->write_to_pipe && !command->read_from_pipe)
			{
				pid = fork();
				if (!pid)
				{
					close(fd[0]);
					dup2(fd[1], 1);
					ft_exec_bin(fresh, command);
					exit(0);
				}
				else
				{
					close(fd[1]);
					fresh->last_fd = dup(fd[0]);
					close(fd[0]);
					wait(NULL);
				}
			}
			if (command->read_from_pipe && command->write_to_pipe)
			{
				pid = fork();
				if (!pid)
				{
					dup2(fresh->last_fd, 0);
					dup2(fd[1], 1);
					close(fd[1]);
					ft_exec_bin(fresh, command);
					exit(0);
				}
				else
				{
					close(fd[1]);
					fresh->last_fd = dup(fd[0]);
					close(fd[0]);
					wait(NULL);
				}
			}
			if (command->read_from_pipe && !command->write_to_pipe)
			{
				pid = fork();
				if (!pid)
				{
					close(fd[0]);
					dup2(fresh->last_fd, 0);
					ft_exec_bin(fresh, command);
					exit(0);
				}
				else
				{
					close(fd[1]);
					close(fd[0]);
					close(fresh->last_fd);
					wait(NULL);
				}
			}
			if (last_out != NULL)
			{
				close(last_out->fd);
				dup2(fresh->fd_out, 1);
			}
		}
		list_elem = list_elem->next;
	}
}

int	main(int argc, char **argv, char **envp, char **apple)
{
	int		reading;
	
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_backslash);
	fresh = malloc(sizeof(t_fresh));
	ft_initialize(fresh);
	ft_load_env_vars(fresh, envp);
	/*esto hay que liberarlo en algun lado*/
	if (variable_get(fresh->env, "USER"))
		fresh->user = ft_strdup(variable_get(fresh->env, "USER")->value);
	else
		fresh->user = ft_strdup("Unknown");
	ft_print_header(fresh);
	fresh->pid = 0;
	reading = 1;
	while (reading)
	{
		read_line(fresh);
		if (!ft_valid_multiline(fresh))
			ft_print_error(fresh, "Multiline commands not supported\n");
		else
			ft_parse_line(fresh);
		free(fresh->line);
		fresh->line = NULL;
		ft_execute_commands(fresh);
		ft_free_commands(fresh);
		ft_print_input(fresh);
	}
	free(fresh);
}
