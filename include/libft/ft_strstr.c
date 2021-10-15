/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:06:03 by bclerc            #+#    #+#             */
/*   Updated: 2021/08/28 17:35:54 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *src, const char *find)
{
	int	i;
	int	b;

	i = 0;
	if (!*find)
		return ((char *)src);
	while (src[i])
	{
		b = 0;
		while (src[i + b] == find[b] && find[b])
			b++;
		if (!find[b])
			return ((char *)&src[i]);
		i++;
	}
	return (0);
}
