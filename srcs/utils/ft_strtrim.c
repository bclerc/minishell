/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:24:19 by user42            #+#    #+#             */
/*   Updated: 2021/10/15 13:10:08 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_find_char(char c, char const *set)
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

char			*ft_strtrim(char const *s1, char set)
{
	int		i;
	int		start;
	int		end;
	char	*res;

	start = 0;
	end = ft_strlen((char *)s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[start] && ft_find_char(s1[start], set))
		start++;
	while (start < end && ft_find_char(s1[end - 1], set))
		end--;
	printf("s = %d\n", end);
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (start < end)
		res[i++] = s1[start++];
	res[i] = '\0';
	printf("res = %s\n", res);
	return (res);
}
