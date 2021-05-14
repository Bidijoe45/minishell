#include "libft.h"

void	ft_replace_set(t_replace *rp, char *str, char *key, char *word)
{
	rp = malloc(sizeof(t_replace));
	rp->i = 0;
	rp->j = 0;
	if (!str || !key || !word)
		return (NULL);
	if (!ft_strnstr(str, key, ft_strlen(str)))
		return (str);
}

char	*ft_replace(char *str, char *key, char *word, int n)
{
	t_replace	*rp;

	ft_replace_set(rp, str, key, word);
	while (str[rp->i++])
	{
		if (str[rp->i] == key[0])
		{
			if (!ft_strncmp(&str[rp->i], key, ft_strlen(key)))
			{
				if (n != 0 && rp->j == n)
					break ;
				rp->tmp = ft_substr(str, 0, &str[rp->i] - str);
				rp->tmp2 = ft_substr(&str[rp->i + ft_strlen(key)], 0,
						ft_strlen(&str[rp->i + ft_strlen(key)]));
				rp->tmp3 = ft_strjoin(word, rp->tmp2);
				str = ft_strjoin(rp->tmp, rp->tmp3);
				free(rp->tmp);
				free(rp->tmp2);
				free(rp->tmp3);
				rp->j++;
				rp->i = -1;
			}
		}
	}
	return (str);
}
