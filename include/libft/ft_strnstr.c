/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:45:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:42:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	size_t	i;
	size_t	b;
	size_t	lentmp;

	lentmp = len;
	if (!*find)
		return ((char *)src);
	i = 0;
	while (lentmp > 0 && src[i])
	{
		b = 0;
		while (src[i + b] == find[b] && find[b])
			b++;
		if (!find[b] && i + b < len + 1)
			return ((char *)&src[i]);
		i++;
		lentmp--;
	}
	return (NULL);
}
