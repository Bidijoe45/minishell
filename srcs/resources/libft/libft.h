/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 11:36:19 by apavel            #+#    #+#             */
/*   Updated: 2021/04/02 14:00:08 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_replace
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;
	int		j;
}				t_replace;

size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(const char *s, char c);
char			**ft_split_ignore_quotes(const char *s, char c);
char			*ft_itoa(int n);
void			ft_putstr_fd(char *s, int fd);
int				ft_lstsize(t_list *lst);
char			*ft_replace(char *str, char *key, char *word, int n);
void			ft_free_split(char **split);
#endif
