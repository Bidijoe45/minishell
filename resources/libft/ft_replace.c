#include "libft.h"

void	replace_aux(t_replace *replace, char **str, char *key, char *word)
{
	replace->tmp = ft_substr(*str, 0, (&(*str))[replace->i] - *str);
	replace->tmp2 = ft_substr(&(*str)[replace->i + ft_strlen(key)], 0,
			ft_strlen(&(*str)[replace->i + ft_strlen(key)]));
	replace->tmp3 = ft_strjoin(word, replace->tmp2);
	*str = ft_strjoin(replace->tmp, replace->tmp3);
	free(replace->tmp);
	free(replace->tmp2);
	free(replace->tmp3);
	replace->j++;
	replace->i = -1;
}

char	*ft_replace(char *str, char *key, char *word, int n)
{
	t_replace	replace;

	replace.i = 0;
	replace.j = 0;
	if (!str || !key || !word)
		return (NULL);
	if (!ft_strnstr(str, key, ft_strlen(str)))
		return (str);
	while (str[replace.i])
	{
		if (str[replace.i] == key[0])
		{
			if (!ft_strncmp(&str[replace.i], key, ft_strlen(key)))
			{
				if (n != 0 && replace.j == n)
					break ;
				replace_aux(&replace, &str, key, word);
			}
		}
		replace.i++;
	}
	return (str);
}
