/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:52:52 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 12:06:02 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*tab;
	int		i;

	if (!s)
		return (NULL);
	tab = (char *)malloc((ft_strlen((char *)s) + 2) * sizeof(char));
	if (tab == NULL)
		return (0);
	tmp = (char *)s;
	i = 0;
	while (tmp[i])
	{
		tab[i] = tmp[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strsdup(char *str, char *set)
{
	int	i;
	int	b;

	i = 0;
	while (str[i])
	{
		b = 0;
		while (set[b])
		{
			if (str[i] == set[b])
				return (ft_strndup(str, i + 1));
			b++;
		}
		i++;
	}
	return (0);
}
