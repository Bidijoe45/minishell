#include "includes/fresh.h"

int	ft_is_special_char(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	between_quotes_pos(int sq, int dq)
{
	if (sq)
		return (1);
	if (dq)
		return (2);
	return (0);
}

int	is_between_quotes2(char *str, int pos)
{
	int	i;
	int	sq;
	int	dq;

	if (!str || !*str)
		return (0);
	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && dq == 0)
			sq = !sq;
		if (str[i] == '"' && sq == 0)
			dq = !dq;
		if (i == pos)
			return (between_quotes_pos(sq, dq));
		i++;
	}
	return (0);
}

int	is_between_quotes(char *str, int pos)
{
	int	i;
	int	sq;
	int	dq;

	if (!str || !*str)
		return (0);
	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i += 2;
			continue ;
		}
		if (str[i] == '\'' && dq == 0)
			sq = !sq;
		if (str[i] == '"' && sq == 0)
			dq = !dq;
		if (i == pos)
			return (between_quotes_pos(sq, dq));
		i++;
	}
	return (0);
}
