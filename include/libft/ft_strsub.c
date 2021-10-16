/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 23:05:59 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:35:14 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		b;
	char	*rt;

	if (!s)
		return (NULL);
	rt = (char *)malloc((len + 1) * sizeof(char));
	if (!rt)
		return (0);
	i = start;
	b = 0;
	while (b < (int)len)
	{
		rt[b] = s[i];
		b++;
		i++;
	}
	rt[b] = '\0';
	return (rt);
}
