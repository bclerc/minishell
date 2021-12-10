/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:18:03 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/10 18:07:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_countword(char const *s, char c)
{
	int count_word;
	int i;

	count_word = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c || s[i] != ' ') && (s[i + 1] == c || s[i + 1] == ' ' || s[i + 1] == '\0'))
			count_word++;
		i++;
	}
	return (count_word);
}

static size_t	ltab(char const *s, int i, char c)
{
	size_t len;

	len = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == ' ')
			return (len);
		len++;
		i++;
	}
	return (len);
}

// j'ai ptet tout casse ici
char			**ft_strsplit_s(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	k = 0;
	tab = malloc(sizeof(char*) * (ft_countword(s, c) + 2));
	if (!tab)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c || s[i] != ' ')
		{
			if (k == 0)
			{
				tab[j] = malloc(sizeof(char) * (ltab(s, i, c) + 2));
				if (!tab)
					return (NULL);
			}
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((((s[i] != c && (s[i + 1] == c || !s[i + 1])) || (s[i] != ' ' && (s[i + 1] == ' ' || !s[i + 1]))) 
			&& k > 0) && !(k = 0))
			j++;
	}
	tab[j] = NULL;
	return (tab);
}