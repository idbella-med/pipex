#ifndef HELP_H
#define HELP_H

#include <unistd.h>

char **ft_split(char *str, char c);
size_t  ft_strlen(char *str);
char *ft_strjoin(char *str1, char *str2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif