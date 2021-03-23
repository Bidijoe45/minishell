
#ifndef LIST_H
# define LIST_H

#include "../fresh.h"

t_list	*list_new_element(void *content);
void	list_add_back(t_list *list, t_list *new_elem);

#endif
