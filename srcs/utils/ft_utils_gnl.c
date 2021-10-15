#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*copy_s;

	i = 0;
	j = 0;
	if (!(copy_s = malloc(sizeof(char) * (len - start) + 1)))
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			copy_s[j++] = s[i];
		i++;
	}
	copy_s[j] = '\0';
	return (copy_s);
}
