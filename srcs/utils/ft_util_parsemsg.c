/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_parsemsg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:22 by astrid            #+#    #+#             */
/*   Updated: 2022/01/12 16:17:28 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concatenation quand tmp n est pas au depart de la str
char	*ft_retneg(int i, char *str, char *tmp, char *new)
{
	int	start;
	int	size;
	int	j;

	start = 0;
	j = 0;
	while (start < i)
	{
		new[start] = str[start];
		start++;
	}
	size = ft_strlen(tmp) + start;
	j = 0;
	while (start <= size)
		new[start++] = tmp[j++];
	size = ft_strlen(str) - 2;
	while (start < size)
	{
		new[start++] = str[i + 1];
		i++;
	}
	new[start] = '\0';
	return (new);
}

// concatenation quand tmp est au depart de la str
char	*ft_retnoneg(int i, char *str, char *tmp, char *new)
{
	int	start;
	int	size;
	int	j;

	start = 0;
	j = 0;
	while (start < i - 2)
	{
		new[start] = tmp[start];
		start++;
	}
	size = ft_strlen(str) - 2;
	while (start <= size)
	{
		new[start] = str[i];
		start++;
		i++;
	}
	new[start] = '\0';
	return (new);
}

char	*ft_special_cat(char *str, char *tmp, int i, int ret)
{
	char	*new;
	int		size;

	size = ft_strlen(str) - 1;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	if (ret == -1)
		new = ft_retneg(i, str, tmp, new);
	else
		new = ft_retnoneg(i, str, tmp, new);
	return (new);
}

char	*ft_special_cat_export(char *str, char *tmp, int i, int ret)
{
	char	*new;
	int		size;

	size = ft_strlen(str);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	if (ret == -1)
		new = ft_retneg(i, str, tmp, new);
	else
		new = ft_retnoneg(i, str, tmp, new);
	return (new);
}

char	*ft_cut_quote(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = ft_strlen(str) - start;
	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (start <= end)
		dest[i++] = str[start++];
	if (i < size - 1)
	{
		while (i < size)
		{
			dest[i] = str[start + 1];
			start++;
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_cut_quote_export(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = ft_strlen(str) - start;
	i = 0;
	dest = malloc(sizeof(char) * (size + 2));
	if (!dest)
		return (NULL);
	while (start <= end)
		dest[i++] = str[start++];
	dest[i] = '^';
	i++;
	if (i < size -1)
	{
		while (i < size)
		{
			dest[i] = str[start + 1];
			start++;
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
