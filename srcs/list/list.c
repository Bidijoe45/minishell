/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 12:55:25 by alvrodri          #+#    #+#             */
/*   Updated: 2021/05/02 12:55:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fresh.h"

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
