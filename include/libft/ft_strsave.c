/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:59:05 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:41:02 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsave(char *s, char c)
{
	int		i;
	char	*pt;

	if (!s)
		return (0);
	i = 0;
	pt = NULL;
	while (s[i])
	{
		if (s[i] == c)
		{
			pt = ft_memcpy(pt, &s, ft_strlen(&*s));
			if (!pt)
				return (NULL);
			else
				return (pt);
		}
		i++;
	}
	return (NULL);
}
