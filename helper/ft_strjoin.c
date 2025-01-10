#include "help.h"

char *ft_strjoin(char *str1, char *str2)
{
    int j;
    int i;
    char *join;

    join = malloc((ft_strlen(str2) + ft_strlen(str1) + 1) * sizeof(char));
    if(!join)
        return(NULL);
    i = 0;
    j = 0;
    while(str1[i])
        join[j++] = str1[i++];
    i = 0;
    while(str2[i])
        join[j++] = str2[i++];
    join[j] = '\0';
    return(join);
}
