/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:46:15 by alvrodri          #+#    #+#             */
/*   Updated: 2021/02/18 11:46:54 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

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
	arr = malloc(sizeof(char *) * size);
	tmp = list;
	while (tmp)
	{
		arr[i] = ft_strjoin(ft_strjoin(((t_variable *)tmp->content)->key, "="), ((t_variable *)tmp->content)->value);
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

t_command	*command_new(char *cmd, char *arg, t_ctype type)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	command->cmd = cmd;
	command->arg = arg;
	command->type = type;
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
	path = ft_strtrim(command->cmd, "\n");
	if (!lstat(path, &f_stat) && !S_ISDIR(f_stat.st_mode))
		return (path);
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
	free(paths);
	return (NULL);
}

 void sigint_handler()
{
	printf("killing process %d\n",getpid());
}

int		ft_exec_bin(t_fresh *fresh, t_command *command)
{
	int		pid;
	int		status;
	char	**argv;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		path = ft_check_if_valid(fresh, command);
		argv = ft_create_argv(command, path);
		if (path)
			execve(path, argv, ft_list_to_chararr(fresh->env));
		else
		{
			free_bidimensional(argv);
			argv = NULL;
			free(path);
			path = NULL;
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
	if (!ft_strncmp(command->cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(command->cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(command->cmd, "export", 6))
		return (1);
	if (!ft_strncmp(command->cmd, "env", 3))
		return (1);
	if (!ft_strncmp(command->cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(command->cmd, "exit", 4))
		exit(0);
	return (0);
}


void    ft_parse_command(t_fresh *fresh, t_command *command)
{
	int	status;
	
	if (command->type == simple)
	{
		if (ft_is_builtin(command))
			;
		else
		{
			if ((status = ft_exec_bin(fresh, command)) != 0)
				ft_printf("\033%s%s\033%s%s%d\n", RED, "Error: ", RESET, "failed with error code ", status);
		}
	}
	ft_print_input(fresh);
}
