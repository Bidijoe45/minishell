#include "libft.h"

char    *ft_replace(char *str, char *key, char *word, int n)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !key || !word)
		return (NULL);
	if (!ft_strnstr(str, key, ft_strlen(str)))
		return (str);
	while (str[i])
	{
		if (str[i] == key[0])
		{
			if (!ft_strncmp(&str[i], key, ft_strlen(key)))
			{
				if (n != 0 && j == n)
					break ;
				tmp = ft_substr(str, 0, &str[i] - str);
				tmp2 = ft_substr(&str[i + ft_strlen(key)], 0,
						ft_strlen(&str[i + ft_strlen(key)]));
				tmp3 = ft_strjoin(word, tmp2);
				str = ft_strjoin(tmp, tmp3);
				free(tmp);
				free(tmp2);
				free(tmp3);
				j++;
				i = -1;
			}
		}
		i++;
	}
	return (str);
}
