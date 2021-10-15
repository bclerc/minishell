/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:34:24 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:41:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;
	char	*last;

	i = 0;
	last = 0;
	tmp = (char *)s;
	while (tmp[i])
	{
		if (tmp[i] == c)
			last = &tmp[i];
		i++;
	}
	if (!tmp[i] && !c)
		return (&tmp[i]);
	return (last);
}
