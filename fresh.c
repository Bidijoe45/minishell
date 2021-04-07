/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:32 by apavel            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 12:32:15 by apavel           ###   ########.fr       */
=======
/*   Updated: 2021/04/07 11:53:13 by alvrodri         ###   ########.fr       */
>>>>>>> 28fdf008f0994d0a85a5b9b24f4f7f222959619d
/*                                                                            */
/* ************************************************************************** */

#include "fresh.h"
#include "commands/command.h"
#include "music.h"
#include "print/print.h"
#include "parser/parser.h"
#include "list/list.h"

void	ft_initialize(t_fresh *fresh)
{
	fresh->cmd_return = 0;
	fresh->env = NULL;
	fresh->line = NULL;
	fresh->local_vars = NULL;
	fresh->user = NULL;
	fresh->commands = NULL;
}

void	ft_signal(int signum)
{
	return ;
}

void	ft_quit(int signum)
{
	return ;
}

void	ft_load_env_vars(t_fresh *fresh, char **envp)
{
	char 	**split_var;
	int		i;
	t_variable	*var;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
		{
			i++;
			continue ;
		}
		split_var = ft_split(envp[i], '=');
		var = variable_new(ft_strdup(split_var[0]), ft_strdup(split_var[1]));
		if (fresh->env)
			list_add_back(fresh->env, list_new_element(var));
		else
			fresh->env = list_new_element(var);
		i++;
		ft_free_split(split_var);
	}
}

void	ft_free_commands(t_fresh *fresh)
{
	t_list *list_elem;
	list_elem = fresh->commands;
	int	i;

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

int		ft_listsize(t_list *list)
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
	int		size;
	int		i;

	size = ft_listsize(list);
	i = 0;
	arr = malloc(sizeof(char *) * (size + 1));
	tmp = list;
	while (tmp)
	{
		if (((t_variable *)tmp->content)->value != NULL)
			arr[i] = ft_strjoin(ft_strjoin(((t_variable *)tmp->content)->key, "="), ((t_variable *)tmp->content)->value);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_create_argv(t_command *command, char *path)
{
	char	**argv;
	char	**arg;
	int		argc;
	int		i;
	int		j;

	argc = 0;
	i = 1;
	j = 0;
	while (command->args[argc])
		argc++;
	argv = malloc(sizeof(char *) * (argc + 2));
	argv[0] = path;
	while (j < argc)
	{
		argv[i] = command->args[j];
		i++;
		j++;
	}
	argv[i] = NULL;
	//free_bidimensional(arg);
	arg = NULL;
	return (argv);
}

char	*create_path(char *path, char *cmd)
{
	char	*tmp;

	tmp = path;
	path = ft_strjoin(path, "/");
	free(tmp);
	tmp = path;
	path = ft_strjoin(path, cmd);
	free(tmp);
	tmp = path;
	path = ft_strtrim(path, "\n");
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
	paths = ft_split(variable_get(fresh->env, "PATH")->value, ':');
	while (paths[i])
	{
		path = create_path(paths[i], command->cmd);
		status = lstat(path, &f_stat);
		if (!status)
		{
			free(paths);
			return (path);
		}
		i++;
	}
	if (path)
		free(path);
	path = ft_strtrim(command->cmd, "\n");
	if (!lstat(path, &f_stat) && !S_ISDIR(f_stat.st_mode))
		return (path);
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

	pid = fork();
	if (pid == 0)
	{
		path = ft_check_if_valid(fresh, command);
		argv = ft_create_argv(command, path);
		chararr = ft_list_to_chararr(fresh->env);
		if (path)
			execve(path, argv, chararr);
		else
		{ 
			//free_bidimensional(argv);
			argv = NULL;
			free(path);
			path = NULL;
			printf("%s: command not found\n", command->cmd);
			//free_bidimensional(chararr);
			exit(127);
		}
		//free_bidimensional(argv);
		argv = NULL;
		exit(errno);
	}
	else
		wait(&status);
	fresh->cmd_return = status >> 8; 
	return (status);
}

int		ft_is_builtin(t_fresh *fresh, t_command *command)
{
	char *name;

	name = command->cmd;
	if (!ft_strncmp(name, "echo", 4))
		return (1);
	else if (!ft_strncmp(name, "cd", 2))
		return (1);
	else if (!ft_strncmp(name, "export", 6))
		return (1);
	else if (!ft_strncmp(name, "env", 3))
		return (1);
	else if (!ft_strncmp(name, "unset", 5))
		return (1);
	else if (!ft_strncmp(name, "pwd", 3))
		return (1);
	else if (!ft_strncmp(name, "exit", 4))
		return (1);
	return (0);
}

void	ft_execute_builtin(t_command *command, t_fresh *fresh)
{
	char *name;

	name = command->cmd;
	if (!ft_strncmp(name, "echo", 4))
		fresh->cmd_return = ft_echo(command, fresh);
	else if (!ft_strncmp(name, "cd", 2))
		fresh->cmd_return = ft_cd(command, fresh);
	else if (!ft_strncmp(name, "export", 6))
		fresh->cmd_return = ft_export(command, fresh);
	else if (!ft_strncmp(name, "env", 3))
		fresh->cmd_return = ft_env(command, fresh);
	else if (!ft_strncmp(name, "unset", 5))
		return ;
	else if (!ft_strncmp(name, "pwd", 3))
		fresh->cmd_return = ft_pwd(command, fresh);
	else if (!ft_strncmp(name, "exit", 4))
		fresh->cmd_return = ft_exit(command, fresh);
	else
		return ;
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
					last_out->fd = open(last_out->file_name, O_RDWR | O_CREAT, 0700);
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
			if (last_out != NULL)
			{
				fresh->fd_out = dup(1);
				dup2(last_out->fd, 1);
			}
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
		/*
		 * POR QUE NO PUEDO HACER FREE JODER....
		 * ni free(command->cmd);
		 * SE SUPOONE QUE TIENE QUE ESTAR TODO ALOCADO
		 * ...........
		 * non-sense
		 * free(command);
		 * */
		list_elem = list_elem->next;
	}
}

int		main(int argc, char **argv, char **envp, char **apple)
{
	t_fresh *fresh;
	int		reading;

	//signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	fresh = malloc(sizeof(t_fresh));
	ft_initialize(fresh);
	ft_load_env_vars(fresh, envp);
	fresh->user = variable_get(fresh->env, "USER")->value;
	ft_print_header(fresh);
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
		//ejecutar comandos
		ft_execute_commands(fresh);
		ft_free_commands(fresh);
		ft_print_input(fresh);
	}

	//Creo que aqui nunca llega xD
	free(fresh);
}
