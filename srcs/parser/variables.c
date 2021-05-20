#include "includes/fresh.h"

void	replace_variables_key(t_fresh *fresh, int i)
{
	int			end;
	char		*tmp_str;
	char		*tmp;
	t_variable	*var;

	end = i;
	while (fresh->line[end]
		&& fresh->line[end] != ' ' && fresh->line[end] != '\n')
		end++;
	tmp_str = ft_substr(fresh->line, i, end - i);
	var = variable_get(fresh->env, tmp_str + 1);
	tmp = fresh->line;
	if (var == NULL)
		fresh->line = ft_replace(fresh->line, tmp_str, "", 0);
	else
		fresh->line = ft_replace(fresh->line, tmp_str, var->value, 0);
	free(tmp);
	free(tmp_str);
}

void	replace_variables(t_fresh *fresh)
{
	int		i;
	char	*pos;
	int		dq;
	int		sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (fresh->line[i] != '\0')
	{
		if (fresh->line[i] == '\\')
			i += 2;
		if (fresh->line[i] == '"' && sq == 0)
			dq = !dq;
		if (fresh->line[i] == '\'' && dq == 0)
			sq = !sq;
		if (fresh->line[i] == '$')
			replace_variables_key(fresh, i);
		i++;
	}
}

void	ft_replace_vars_aux(t_fresh *fresh, char *cmds, t_replace_vars *r_vars)
{
	r_vars->pos = r_vars->i;
	r_vars->pos++;
	while (r_vars->ret[r_vars->pos] != ' ' && r_vars->ret[r_vars->pos] != '$'
		&& r_vars->ret[r_vars->pos]
		!= '"' && r_vars->ret[r_vars->pos] != '\''
		&& r_vars->ret[r_vars->pos] != '\\' && r_vars->ret[r_vars->pos] != '\0')
		r_vars->pos++;
	r_vars->key = ft_substr(r_vars->ret, r_vars->i, r_vars->pos - r_vars->i);
	r_vars->tmp = r_vars->ret;
	r_vars->var = variable_get(fresh->env, r_vars->key + 1);
	if (r_vars->var)
		r_vars->ret = ft_replace(r_vars->ret, r_vars->key,
				r_vars->var->value, 0);
	else
		r_vars->ret = ft_replace(r_vars->ret, r_vars->key, "", 0);
	free(r_vars->tmp);
	free(r_vars->key);
	r_vars->i = 0;
}

char	*ft_replace_vars(t_fresh *fresh, char *cmds)
{
	t_replace_vars	*r_vars;

	r_vars = malloc(sizeof(t_replace_vars));
	r_vars->i = 0;
	r_vars->ret = ft_strdup(cmds);
	while (r_vars->ret[r_vars->i])
	{
		if (r_vars->ret[r_vars->i] == '\\')
			r_vars->i += 2;
		if (r_vars->ret[r_vars->i] == '$' && r_vars->ret[r_vars->i + 1]
			&& r_vars->ret[r_vars->i + 1] != '?'
			&& r_vars->ret[r_vars->i + 1] != '"' && r_vars->ret[r_vars->i + 1]
			!= '\'' && is_between_quotes(r_vars->ret, r_vars->i) != 1)
			ft_replace_vars_aux(fresh, cmds, r_vars);
		else
			r_vars->i++;
	}
	return (r_vars->ret);
}
