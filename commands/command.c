/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/03/05 12:38:35 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"
#include "../print/print.h"

void    ft_not_found(char *cmd)
{
	ft_print_color(RESET, "");
	ft_print_color(RED, "Command not found: ");
	ft_print_color(RESET, cmd);
}

int		ft_is_variable(char *command)
{	
	if (ft_strchr(command, '='))
		return (1);
	return (0);
}

//TODO: si una variable local es cambiada tambien tiene que cambiar en export
void    new_local_var(t_fresh *fresh, char *cmd)
{
	char        **split_cmd;
	t_variable  *var;

	split_cmd = ft_split(cmd, '=');
	if (split_cmd[1] == NULL)
		return ft_not_found(cmd);
	if (fresh->local_vars)
	{
		variable_set(fresh->local_vars, split_cmd[0], split_cmd[1]);
		variable_mod(fresh->env, split_cmd[0], split_cmd[1]);
	}
	else
		fresh->local_vars = list_new_element(variable_new(split_cmd[0], split_cmd[1]));
	free(split_cmd);
}

//=========TEST ONLY============
static void	list_print(t_list *list)
{
	t_list *elem;

	if (!list)
	{
		ft_printf("lista vacia\n");
		return ;
	}

	ft_printf("--LIST START--\n");
	elem = list;
	while (elem)
	{	
		if (elem->content)
		{
			ft_printf("key: %s\n", ((t_variable *)elem->content)->key);
			ft_printf("value: %s\n", ((t_variable *)elem->content)->value);
		}
		else
			ft_printf("no content\n");
		elem = elem->next;
	}
	ft_printf("--LIST END--\n");
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
		arr[i] = ft_strjoin(ft_strjoin(((t_variable *)tmp->content)->key, "="), ((t_variable *)tmp->content)->value);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

t_command	*command_new(char *cmd, char *arg, t_ctype type, char *redirect)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	command->cmd = cmd;
	command->arg = arg;
	command->type = type;
	if (command->type != f_pipe && command->type != simple)
		command->redirect = redirect;
	else
		command->redirect = NULL;
	return (command);
}

void	*command_set(t_list **list, t_command *command)
{
	if (!*list)
		*list = list_new_element(command);
	else
		list_add_back(*list, list_new_element(command));
	return NULL;
}

//=========TEST ONLY============
void	command_print_list(t_list *list)
{
	if (!list)
		printf("lista de comandos vacia\n");
	
	t_list *elem;

	elem = list;
	while (elem)
	{
		t_command *cmd = (t_command *)elem->content;
		printf("--command--\n");
		printf("cmd: %s\n",	cmd->cmd);
		printf("arg: %s\n",	cmd->arg);
		printf("type: %u\n", cmd->type);
		printf("\n");
		elem = elem->next;
	}
}

void	free_bidimensional(char **mem)
{
	int i;

	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		mem[i] = NULL;
		i++;
	}
	free(mem);
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
	arg = ft_split(command->arg, ' ');
	while (arg[argc])
		argc++;
	argv = malloc(sizeof(char *) * (argc + 2));
	argv[0] = path;
	while (i <= argc)
	{
		argv[i] = i == argc ? ft_strtrim(arg[j], "\n") : ft_strdup(arg[j]);
		i++;
		j++;
	}
	argv[i] = NULL;
	free_bidimensional(arg);
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
	//FIXME: memory leak
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
			free_bidimensional(argv);
			argv = NULL;
			free(path);
			path = NULL;
			free_bidimensional(chararr);
			exit(127);
		}
		free_bidimensional(argv);
		argv = NULL;
		exit(errno);
	}
	else
		wait(&status);
	return (status);
}

int		ft_is_builtin(t_command *command)
{
	if (!ft_strncmp(command->cmd, "echo", 4))
		return (1);
	else if (!ft_strncmp(command->cmd, "cd", 2))
		chdir("/");
	else if (!ft_strncmp(command->cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(command->cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(command->cmd, "env", 3))
		return (1);
	else if (!ft_strncmp(command->cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(command->cmd, "exit", 4))
		ft_exit();
	else
		return (0);
	return (1);
}

void    ft_parse_command(t_fresh *fresh, t_command *command, t_command *next)
{
	int	status;
	int	pid;
	
	if (command->type == simple)
	{
		if (ft_is_builtin(command))
		{
			;
		}
		else
		{
			if ((status = ft_exec_bin(fresh, command)) == 32512)
				ft_print_error(fresh, "Command not found");
		}
	}
	else if (command->type == f_pipe)
	{
		pipe(command->fd);
		pid = fork();

		if (pid == 0)
		{
			if (fresh->last_fd != 0)
				dup2(fresh->last_fd, 0);
			if (next != NULL)
				dup2(command->fd[1], 1);
			close(command->fd[0]);
			ft_exec_bin(fresh, command);
			exit(errno);
		}
		else
		{
			wait(NULL);
			close(command->fd[1]);
			fresh->last_fd = command->fd[0];
		}
	}
	else if (command->type == s_redirect || command->type == d_redirect) /* >? */
	{
		pid = fork();

		if (pid == 0)
		{
			command->file = open(command->redirect, O_RDWR | (command->type == s_redirect ? 0 : O_APPEND) | O_CREAT, 700);
			if (command->file)
				dup2(command->file, 1);
			if ((status = ft_exec_bin(fresh, command)) == 32512)
				ft_print_error(fresh, "Command not found");
			close(command->file);
			exit(errno);
		}
		else
			wait(NULL);
	}
}

void	exec_commands(t_fresh *fresh)
{
	int		i;
	t_list *list_elem = fresh->commands;

	i = 0;
	fresh->last_fd = 0;
	while (list_elem)
	{
		t_command *command = ((t_command *)list_elem->content);
		command->index = i;
		ft_parse_command(fresh, command, (t_command *)list_elem->next);
		free(command->arg);
		free(command->cmd);
		if (command->redirect)
			free(command->redirect);
		free(command);
		free(list_elem);
		list_elem = list_elem->next;
		i++;
	}
	fresh->commands = NULL;
	free(fresh->commands);
	ft_print_input(fresh);
}
