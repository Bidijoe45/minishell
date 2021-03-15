#include "../fresh.h"
#include "../commands/command.h"

void	sort_list(t_list *list)
{
	t_list 	*i;
	t_list 	*j;
	t_list	*tmp;

	i = list;
	while (i)
	{
		j = i->next;
		if (((t_variable *)i)->value[0] > ((t_variable *)j)->value[0])
		{
			tmp = j->next;
			j->next = i;
			i->next = tmp;
		}
		else
			i = i->next;
	}
}

void	print_list(t_list *list)
{
	t_list	*i;
	t_variable *var;

	i = list;
	while (i)
	{
		var = (t_variable *)i;
		printf("declare -x %s=%s", var->key, var->value);
		i = i->next;
	}
}
