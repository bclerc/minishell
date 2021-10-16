/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/15 13:31:15 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	int count_word;
	int i;

	count_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
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
		if (s[i] == c)
			return (len);
		len++;
		i++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	k = 0;
	tab = malloc(sizeof(char*) * (ft_countword(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (k == 0)
				tab[j] = malloc(sizeof(char) * (ltab(s, i, c) + 1));
				if (!tab)
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((s[i] != c && (s[i + 1] == c || !s[i + 1]) && k > 0) && !(k = 0))
			j++;
	}
	tab[j] = NULL;
	return (tab);
}