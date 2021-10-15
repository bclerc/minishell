/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:25:32 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:54:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = dest;
	i = 0;
	while (i < n)
	{
		tmp[i] = ((unsigned char *)src)[i];
		if (tmp[i] == (unsigned char)c)
		{
			i++;
			return (&dest[i]);
		}
		i++;
	}
	return (NULL);
}
