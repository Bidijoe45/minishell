/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:18:07 by apavel            #+#    #+#             */
/*   Updated: 2021/04/30 12:50:10 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;
	int		dq;
	int		sq;

	dq = 0;
	sq = 0;
	words = 0;
	i = 0;
	if (s[0] != c)
		words++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
			i += 2;
		if (s[i] == '"' && sq == 0)
			dq = !dq;
		if (s[i] == '\'' && dq == 0)
			sq = !sq;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0'
			&& (sq == 0 && dq == 0))
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_next_sep(const char *s, char c)
{
	size_t	i;
	int		dq;
	int		sq;

	sq = 0;
	dq = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
		{
			i += 2;
		}
		if (s[i] == '"' && sq == 0)
			dq = !dq;
		if (s[i] == '\'' && dq == 0)
			sq = !sq;
		if (s[i] == c && sq == 0 && dq == 0)
			return (i);
		i++;
	}
	return (i);
}

static void	ft_alloc_wrds(char **table, const char *s, char c, size_t words)
{
	size_t	i;
	size_t	j;
	int		dq;
	int		sq;
	int		sep;

	sq = 0;
	dq = 0;
	i = 0;
	j = 0;
	while (i < words)
	{
		if (s[j] == '\\')
			j += 2;
		if (s[j] == '"' && sq == 0)
			dq = !dq;
		if (s[j] == '\'' && dq == 0)
			sq = !sq;
		while (s[j] == c && s[j] != '\0' && (sq == 0 && dq == 0))
			j++;
		sep = ft_next_sep(&s[j], c);
		table[i++] = ft_substr(s, j, sep);
		j += sep;
	}
	table[i] = NULL;
}

char	**ft_split_ignore_quotes(const char *s, char c)
{
	char	**table;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	table = malloc(sizeof(char *) * (words + 1));
	if (!table)
		return (NULL);
	if (s[0] == '\0')
	{
		table[0] = NULL;
		return (table);
	}
	if (s && !ft_strchr(s, c))
	{
		table[0] = ft_strdup(s);
		table[1] = NULL;
	}
	else
		ft_alloc_wrds(table, s, c, words);
	return (table);
}
