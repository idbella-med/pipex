#include "help.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (needle[j] == '\0')
		return ((char *)(haystack));
	while (haystack[i] && i < len)
	{
        j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] && (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
		
	}
	return (0);
}