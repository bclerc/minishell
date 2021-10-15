/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:49:29 by bclerc            #+#    #+#             */
/*   Updated: 2018/11/14 12:11:26 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < (int)n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (i < (int)n && ((s1[i] && !s2[i]) || ((s2[i] && !s1[i]))))
		return (0);
	return (1);
}
