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
