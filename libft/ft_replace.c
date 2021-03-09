#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        str = strstr(str, key);
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
    key_pos = malloc(sizeof(char *) * key_count);
    i = 0;
    while(i < key_count)
    {
        str = strstr(str, key);
        key_pos[i] = str;
        str++;
        i++;
    }
    return (key_pos);
}

void    replace_keys()
{
    int word_len;
    int i;
    int j;
    int k;
    int l;

    
}

char    *ft_replace(char *str, char *key, char *word)
{
    int key_count;
    char *ret_str;
    int ret_str_len;
    char **key_pos;

    int word_len;
    int i;
    int j;
    int k;
    int l;

    key_count = count_keys(str, key);
    ret_str_len = (strlen(str) - (strlen(key) * key_count)) + (strlen(word) * key_count) + 1;
    ret_str = malloc(ret_str_len);
    if (key_count > 0)
        key_pos = get_key_pos(str, key);
    i = 0;
    j = 0;
    l = 0;
    word_len = strlen(word);
    while (i < ret_str_len)
    {
        if (&str[j] == key_pos[l])
        {
           k = 0;
           while (k < word_len)
           {
               ret_str[i] = word[k];
               i++;
               k++;
           }
           j += strlen(key);
           l++;
        }
        else
           ret_str[i++] = str[j++];
    }
    ret_str[ret_str_len] = '\0';
    free(key_pos);
    return (ret_str);
}