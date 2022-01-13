/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 23:05:59 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/13 16:58:39 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*rt;

	if (!s)
		return (NULL);
	rt = (char *)malloc((len + 1) * sizeof(char));
	if (!rt)
		return (0);
	i = 0;
	while (i < (int)len)
	{
		rt[i] = s[i + start];
		i++;
	}
	rt[i] = '\0';
	return (rt);
}
