/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:30 by apavel            #+#    #+#             */
/*   Updated: 2021/04/05 13:43:41 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fresh.h"
#include "command.h"

void	print_list(t_list *list)
 {
 	t_list	*i;
 	t_variable *var;

 	i = list;
 	while (i)
 	{
 		var = (t_variable *)i->content;
 		printf("declare -x %s=%s\n", var->key, var->value);
 		i = i->next;
 	}
 }

void	swap(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sort_list(t_list *list)
{
	t_list	*elem;
	t_list	*next_elem;
	int		swapped;
	int		 i;

	if (list == NULL)
		return ;
	swapped = 1;
	next_elem = NULL;
	while (swapped)
	{
		swapped = 0;
		elem = list;
		while (elem->next != next_elem)
		{
			if (((t_variable *)elem->content)->key[0] > ((t_variable *)elem->next->content)->key[0])
			{
				swap(elem, elem->next);
				swapped = 1;
			}
			elem = elem->next;
		}
		next_elem = elem;
	}
}

int			count_vars(char *arg)
{
	int		i;
	int		count;
	int		dq;
	int		sq;
	i = 0;
	dq = 0;
	sq = 0;
	count = 0;
	
	if (ft_strlen(arg) == 0)
		return (count);
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' && sq == 0)
			dq = !dq;
		if (arg[i] == '\'' && dq == 0)
			sq = !sq;
		if (arg[i] == ' ' && dq == 0 && sq==0 && arg[i - 1] != ' ')
			count++;
		i++;
	}

	return (count + 1);
}

int		check_export(t_fresh *fres, char **split_arg, int vars)
{
	int		i;
	int		j;
	int		dq;
	int		sq;
	int		pos;
	char	**split_var;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	i = 0;
	pos = 0;
	while (i < vars)
	{
		j = 0;
		while (split_arg[i][j] != '\0')
		{
			if (split_arg[i][j] == '"' && sq == 0)
				dq = !dq;
			if (split_arg[i][j] == '\'' && dq == 0)
				sq = !sq;
		}
	}

	return 1;
}

int	validate_variable(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_command *command, t_fresh *fresh)
{
	int		i;
	char	*tmp;
	char	**variable;

	if (!*command->args)
	{
		sort_list(fresh->env);
		print_list(fresh->env);
		return (0);
	}
	if (command->args[0][0] == '-')
	{
		printf("export: options not supported\n");
		return (1);
	}
	i = 0;
	while (command->args[i])
	{
		//TODO: leak probablemente jasjasj me da pereza
		variable = ft_split_ignore_quotes(command->args[i], '=');
		variable[0] = ft_replace(variable[0], "\"", "", 0);
		if (!validate_variable(variable[0]))
		{
			if (variable[1])
				printf("export: `%s=%s': not a valid identifier\n", variable[0], variable[1]);
			else
				printf("export: `%s': not a valid identifier\n", variable[0]);
			return (1);
		}
		printf("(%s=%s)\n", variable[0] ? variable[0] : NULL, variable[1] ? variable[1] : NULL);
		i++;
	}
	return (0);
}
