/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:23:23 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/29 15:17:06 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"
#include "../../includes/print.h"
#include "../../includes/command.h"
#include "../../includes/parser.h"

void	ft_parse_cmd(t_fresh *fresh, char *command)
{
	int			i;
	int			n_pipes;
	char		**cmds;

	n_pipes = 0;
	i = 0;
	cmds = ft_split_ignore_quotes(command, '|');
	while (cmds[n_pipes])
		n_pipes++;
	if (n_pipes - 1 != 0)
		ft_parse_cmd_aux(fresh, cmds, n_pipes);
	else
		ft_parse_instruction(fresh, command, 0, 0);
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	ft_replace_escape_var(t_replace_vars *r_vars)
{
	if (r_vars->ret[r_vars->i + 1] == '$'
		&& is_between_quotes2(r_vars->ret, r_vars->i) != 1)
	{
		r_vars->tmp = r_vars->ret;
		r_vars->ret = ft_replace(r_vars->ret, "\\$", "$", 1);
		free(r_vars->tmp);
	}
}

void	ft_replace_vars_aux(t_fresh *fresh, t_replace_vars *r_vars)
{
	r_vars->pos = r_vars->i;
	r_vars->pos++;
	while ((r_vars->ret[r_vars->pos] >= 'a' && r_vars->ret[r_vars->pos] <= 'z')
		|| (r_vars->ret[r_vars->pos] >= 'A' && r_vars->ret[r_vars->pos] <= 'Z')
		|| r_vars->ret[r_vars->pos] >= '_')
		r_vars->pos++;
	r_vars->key = ft_substr(r_vars->ret, r_vars->i, r_vars->pos - r_vars->i);
	r_vars->tmp = r_vars->ret;
	r_vars->var = variable_get(fresh->env, r_vars->key + 1);
	if (r_vars->var)
	{
		r_vars->ret = ft_replace2(r_vars->ret, r_vars->key,
				r_vars->var->value, 0);
	}
	else
		r_vars->ret = ft_replace(r_vars->ret, r_vars->key, "", 0);
	free(r_vars->tmp);
	free(r_vars->key);
	r_vars->i = 0;
}

char	*ft_replace_vars(t_fresh *fresh, char *cmds)
{
	t_replace_vars	r_vars;

	r_vars.i = 0;
	r_vars.ret = ft_strdup(cmds);
	while (r_vars.ret[r_vars.i])
	{
		if (r_vars.ret[r_vars.i] == '\\')
		{
			ft_replace_escape_var(&r_vars);
			r_vars.i += 2;
			continue ;
		}
		if (r_vars.ret[r_vars.i] == '$' && r_vars.ret[r_vars.i + 1]
			&& r_vars.ret[r_vars.i + 1] != '?'
			&& r_vars.ret[r_vars.i + 1] != '/'
			&& r_vars.ret[r_vars.i + 1] != '"' && r_vars.ret[r_vars.i + 1]
			!= '\'' && is_between_quotes(r_vars.ret, r_vars.i) != 1)
			ft_replace_vars_aux(fresh, &r_vars);
		else
			r_vars.i++;
	}
	return (r_vars.ret);
}

void	ft_parse_line(t_fresh *fresh)
{
	int		i;
	char	**cmds;
	char	*tmp;

	i = 0;
	tmp = fresh->line;
	fresh->line = ft_strtrim(fresh->line, "\n");
	free(tmp);
	if (syntax_checker(fresh))
		return ;
	cmds = ft_split_ignore_quotes(fresh->line, ';');
	i = -1;
	while (cmds[++i])
		ft_parse_cmd(fresh, cmds[i]);
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
}
