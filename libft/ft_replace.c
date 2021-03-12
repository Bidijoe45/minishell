#include "libft.h"

int     count_keys(char *str, char *key)
{
	int end;
	int key_count;
	int i;

	end = 0;
	key_count = 0;
	i = 0;
	while(end == 0)
	{
		str = ft_strnstr(str, key, ft_strlen(str));
		if (str)
		{
			key_count++;
			str++;
		}
		if (!str)
			end = 1;
	}
	return (key_count);
}

char     **get_key_pos(char *str, char *key)
{
	int end;
	int key_count;
	int i;
	char **key_pos;

	end = 0;
	key_count = count_keys(str, key);
	key_pos = malloc(sizeof(char *) * (key_count + 1));
	i = 0;
	while(i < key_count)
	{
		str = ft_strnstr(str, key, ft_strlen(str));
		key_pos[i] = str;
		str++;
		i++;
	}
	key_pos[i] = NULL;
	return (key_pos);
}

void    replace_keys(t_replace *replace, char *str, char *key, char *word)
{
	int key_len;

	key_len = ft_strlen(key);
	while (replace->i < replace->ret_str_len)
	{
		if (&str[replace->j] == replace->key_pos[replace->l])
		{
		   replace->k = 0;
		   while (replace->k < replace->word_len)
		   {
			   replace->ret_str[replace->i] = word[replace->k];
			   replace->i++;
			   replace->k++;
		   }
		   replace->j += key_len;
		   replace->l++;
		}
		else
			replace->ret_str[replace->i++] = str[replace->j++];
	}
}

char    *ft_replace(char *str, char *key, char *word)
{
	t_replace   *replace;
	char		*ret;
	int i;

	replace = malloc(sizeof(t_replace));
	replace->i = 0;
	replace->j = 0;
	replace->k = 0;
	replace->l = 0;
	replace->key_count = count_keys(str, key);
	replace->ret_str_len = (ft_strlen(str) - (ft_strlen(key) * replace->key_count)) + (ft_strlen(word) * replace->key_count) + 1;
	replace->ret_str = malloc(replace->ret_str_len);
	if (replace->key_count > 0)
		replace->key_pos = get_key_pos(str, key);
	replace->word_len = ft_strlen(word);
	replace_keys(replace, str, key, word);
	ret = ft_strdup(replace->ret_str);
	free(replace->ret_str);
	free(replace->key_pos);
	free(replace);
	return (ret);
}