#ifndef PARSE_H
# define PARSE_H

#include "../fresh.h"

int		ft_valid_quotes(char *line);
void    ft_split_commands(t_fresh *fresh, char *line);
void	ft_mini_parse(t_fresh *fresh);

#endif