#include "../fresh.h"
#include "../print/print.h"
#include "../commands/command.h"

int		ft_valid_quotes(char *line)
{
	int dq;
	int sq;
	int i;

	dq = 0;
	sq = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && dq == 0 && sq == 0)
			dq = 1;
		else if (line[i] == '"' && dq == 1)
			dq = 0;

		if (line[i] == '\'' && sq == 0 && dq == 0)
			sq = 1;
		else if (line[i] == '\'' && sq == 1)
			sq = 0;

		i++;
	}
	return (dq == 1 || sq == 1) ? 0 : 1;
}

void replace_variables(t_fresh *fresh)
{
	int i = 0;
	char *pos;
	int dq;
	int sq;
	int end;
	char *tmp_str;
	char	*tmp;
	t_variable *var;

	dq = 0;
	sq = 0;
	end = 0;

	while (fresh->line[i] != '\0')
	{
		if (fresh->line[i] == '\\')
			i += 2;
		if (fresh->line[i] == '"' && sq == 0)
			dq = !dq;
		if (fresh->line[i] == '\'' && dq == 0)
			sq = !sq;
		if (fresh->line[i] == '$')
		{
			end = i;
			while (fresh->line[end] && fresh->line[end] != ' ' && fresh->line[end] != '\n')
				end++;
			tmp_str = ft_substr(fresh->line, i, end - i);
			var = variable_get(fresh->env, tmp_str + 1);
			tmp = fresh->line;
			fresh->line = ft_replace(fresh->line, tmp_str, var == NULL ? "" : var->value);
			free(tmp);
			free(tmp_str);
		}
		i++;
	}
}

int		ft_valid_multiline(t_fresh *fresh)
{
	t_list *commands;
	int  valid_q;

	valid_q = ft_valid_quotes(fresh->line);
	if (valid_q == 1)
		return (1);
	else
		return (0);
}

void	read_line(t_fresh *fresh)
{
	char	c[2];
	int		pos;
	char	*tmp;

	pos = 0;
	while (read(0, c, 1) > 0)
	{
		c[1] = '\0';
		if (!fresh->line)
			fresh->line = ft_strdup(c);
		else
		{
			tmp = fresh->line;
			fresh->line = ft_strjoin(fresh->line, c);
			free(tmp);
		}
		if(fresh->line[pos] == '\n')
			break ;
		pos++;
	}
}

void	ft_parse_args(t_fresh *fresh, t_command *command, char **words)
{
	int	i;

	i = 0;
	if (words == NULL || *words == NULL)
		return ;
	while (words[i])
		i++;
	command->args = malloc(sizeof(char *) * (i + 1));
	if (!command->args)
		return ;
	i = 0;
	while (words[i])
	{
		command->args[i] = ft_strdup(words[i]);
		i++;
	}
}

int		ft_is_special_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*extract_cmd(char *command)
{
	int	i;
	int	pos;
	int	next_is_file;
	
	i = 0;
	pos = 0;
	next_is_file = 0;
	while (command[i] != '\0')
	{
		while (command[i] == ' ')
			i++;
		if (command[i] == '>' || command[i] == '<')
		{
			i++;
			while (command[i] == ' ')
				i++;
			while (command[i] != ' ' && command[i] != '<' && command[i] != '>'
				&& command[i] != '\0')
				i++;
		}
		else
		{
			pos = i;
			while (command[i] != ' ' && command[i] != '>' && command[i] != '<'
				&& command[i] != '\0' && command[i] != '\n')
				i++;
			return ft_substr(command, pos, i - pos);
		}
	}
	return ft_substr(command, pos, i - pos);

}

void	ft_parse_cmd(t_fresh *fresh, char *command)
{
	int i;
	int j;
	char **cmds;
	char	*cmd;
	char	**args;
	char	**files;

	cmds = ft_split_ignore_quotes(command, '|');
	
	int n_pipes = 0;
	while (cmds[n_pipes])
		n_pipes++;
	printf("n_pipes: %d\n", n_pipes);
	
	if (n_pipes - 1 != 0)
	{
		//Si entra aqui es que hay | pipes
	
		i = 0;
		while (cmds[i])
		{
			printf("--ft_parse_cmd--\n");
			printf("%s\n", cmds[i]);
			printf("----\n");
			cmd = extract_cmd(cmds[i]);
			//args = extract_args(cmds[i]);
			//files = extract_files(cmds[i]);
			i++;
			printf("cmd: |%s|\n", cmd);
		}
	}
	else
	{
		//Si entra aqui es que no hay | por lo que es un simple comando
		printf("cmd: |%s|\n", cmd);
	}
}

void	ft_parse_line(t_fresh *fresh)
{
	int		i;
	int		cmd_pos;
	char	**cmds;

	i = 0;
	cmds = ft_split_ignore_quotes(fresh->line, ';');

	while (cmds[i])
	{
		ft_parse_cmd(fresh, cmds[i]);
		i++;
	}

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
