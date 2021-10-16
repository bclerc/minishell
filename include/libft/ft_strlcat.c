/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:59:58 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:46:43 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	in;
	size_t	dest_size;
	size_t	src_size;

	dest_size = ft_strlen(dst);
	src_size = ft_strlen((char *)src);
	in = 0;
	if (dest_size >= size)
		return (src_size + size);
	while (dst[in] && in < (size - 1))
		in++;
	while (*src && in < (size - 1))
	{
		dst[in] = *src;
		src++;
		in++;
	}
	dst[in] = 0;
	return (dest_size + src_size);
}
