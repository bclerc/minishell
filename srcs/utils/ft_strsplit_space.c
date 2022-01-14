/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:46:29 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 13:29:16 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	ft_count_words(const char *str, char *set)
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

static	char	*ft_word(const char *str, char *set, int *i, int status)
{
	char	*s;
	int		k;
	char	save;
	char	*tmp;

	save = 0;
	if (*i == 0 && str[*i] == '$')
	{
		save = str[*i];
		*i += 1;
	}
	else if (*i != 0)
		save = str[*i - 1];
	s = fill(str, set, i);
	replace_var(save, &s, status);
	if (!s)
		return (NULL);
	while (is_in_set(str[*i], set) && str[*i])
		*i += 1;
	return (s);
}

char	**ft_strsplit_s(const char *str, char *set, int status)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	i = 0;
	j = 0;
	wrd = ft_count_words(str, set);
	s = (char **)malloc(sizeof(s) * (ft_count_words(str, set) + 2));
	if (!(s))
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, set, &i, status);
		j++;
	}
	s[j] = NULL;
	return (s);
}
