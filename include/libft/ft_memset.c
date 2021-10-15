/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:47:27 by bclerc            #+#    #+#             */
/*   Updated: 2018/11/07 10:36:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	int				i;
	unsigned char	*tmp;

	tmp = s;
	i = 0;
	while (i < (int)n)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
