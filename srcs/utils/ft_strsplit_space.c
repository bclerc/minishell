
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 18:16:09 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	short	is_a_word(char before, char current, char strip)
{
	return (((before == strip || before == 0) && current != strip)
			||( (before == ' ' || before == 0) && current != ' '));
}

static	int		total_words(char const *s, char strip)
{
	int i;
	int total;

	i = 0;
	total = 0;
	while (s[i])
	{
		if (is_a_word(s[i - 1], s[i], strip))
			total++;
		i++;
	}
	return (total);
}

static	int		word_len(const char *c, char strip)
{
	unsigned int	i;

	i = 0;
	while (c[i] && c[i] != strip && c[i] != ' ')
		i++;
	return (i);
}

char			**ft_strsplit_s(char const *s, char c)
{
	char	**str;
	char	*tmp;
	char	*var;
	char	*env;
	int		i;
	int		stri;

	if (!s || !(str = (char**)malloc((total_words(s, c) + 1) * sizeof(char*))))
		return (NULL);
	tmp = (char*)s;
	i = 0;
	stri = 0;
	while (tmp[i])
	{
		if (is_a_word(i > 0 ? tmp[i - 1] : c, tmp[i], c))
		{
			if (tmp[i - 1] == c)
			{
				var = ft_strndup(&tmp[i], word_len(&tmp[i], c));
				env = get_env_variable(var);
				free(var);
				if (!env)
					str[stri] = ft_strdup("    ");
				else
					str[stri] = ft_strdup(env);
			}
			else
				str[stri] = ft_strndup(&tmp[i], word_len(&tmp[i], c));
			if (!(str[stri]))
			{
				free(str);
				return (NULL);
			}
			stri++;
		}
		i++;
	}
	str[stri] = 0;
	return (str);
}