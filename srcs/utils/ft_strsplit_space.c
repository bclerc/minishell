/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:46:29 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 12:41:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			is_in_set(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int		ft_count_words(const char *str, char *set)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (is_in_set(str[i], set) && !is_in_set(str[i + 1], set))
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static	char	*ft_word(const char *str, char *set, int *i)
{
	char	*s;
	int		k;
	char	*tmp;
	char	save;

	save = 0;
	if (*i == 0 && str[*i] == '$')
	{
		save = str[*i];
		*i += 1;
	}
	else if (*i != 0)
		save = str[*i - 1];
	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while ((!is_in_set(str[*i], set)) && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	if (save == '$')
	{
		tmp = s;
		if (ft_strlen(s) > 0)
			s = ft_strdup(get_env_variable(tmp));
		else
			s = ft_strdup("	");
		free(tmp);
	}
	while (is_in_set(str[*i], set) && str[*i])
		*i += 1;
	return (s);
}

char			**ft_strsplit_s(const char *str, char *set)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	i = 0;
	j = 0;
	wrd = ft_count_words(str, set);
	if (!(s = (char **)malloc(sizeof(s) * (ft_count_words(str, set) + 2))))
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, set, &i);
		j++;
	}
	s[j] = NULL; 
	return (s);
}
