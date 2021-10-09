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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size_s1;
	int		size_s2;
	char	*copy_s;

	i = 0;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(copy_s = (char *)malloc(sizeof(char) * (size_s1 + size_s2 + 1))))
		return (NULL);
	while (s1[i])
	{
		copy_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		copy_s[i] = s2[j];
		i++;
		j++;
	}
	copy_s[i] = '\0';
	return (copy_s);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*copy_s1;

	i = 0;
	copy_s1 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!copy_s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy_s1[i] = (char)s1[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}
