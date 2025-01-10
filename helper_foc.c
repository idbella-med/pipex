#include "pipex.h"

int  count_word(char *str, char c)
{
    int i = 0;
    int n = 0;
    int count = 0;
    while(str[i])
    {
        if(str[i] != c && n == 0)
        {
            count++;
            n = 1;
        }
        else if (str[i] == c)
            n = 0;
        i++;
    }
    return (count);
}

char *word_copy(char *str, char c)
{
    int i = 0;
    char *s;
    while(str[i] && str[i] != c)
        i++;
    s = malloc(i + 1);
    if(!s)
        return (NULL);
    i = 0;
    while(str[i] && str[i] != c)
    {
        s[i] = str[i];
        i++;
    }
    s[i] = '\0';
    return (s);
}

char **ft_split(char *str, char c)
{
    int i = 0;
    int j = 0;
    char **s;
    int n = count_word + 1;
    s = malloc(n * sizeof(char *));
    if(!s)
        return(NULL);
    while (str[i])
    {
        while (str[i] == c && str[i])
            i++;
        if (str[i] != c)
        {
            s[j] = word_copy(str + i, c);
            j++;
        }
        while(str[i] != c && str[i])
            i++;
    }
    return (s);
}

int main()
{
}