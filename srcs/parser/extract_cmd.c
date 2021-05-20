#include "includes/fresh.h"

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
