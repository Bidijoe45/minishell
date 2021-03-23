
#include "../fresh.h"

t_list	*list_new_element(void *content)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	list->content = content;
	list->next = NULL;

	return (list);
}

void	list_add_back(t_list *list, t_list *new_elem)
{
	t_list *elem;

	if (!list)
		return ;

	elem = list;
	while (elem)
	{
		if (elem->next == NULL)
		{
			elem->next = new_elem;
			return ;
		}
		else
			elem = elem->next;
	}
}
