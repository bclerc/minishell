/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_parsemsg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:22 by astrid            #+#    #+#             */
/*   Updated: 2021/11/09 13:22:18 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concatenation quand tmp n est pas au depart de la str
char	*ft_retneg(int i, char *str, char *tmp, char *new)
{
	int start;
	int	size;
	int	j;

	start = 0;
	j = 0;
	while (start < i)
	{
		new[start] = str[start];
		//printf("new[%d] = %c str[%d] = %c\n", start, new[start], start, str[start]);
		start++;
	}
	size = ft_strlen(tmp) + start;
	//printf("tmp = %s s = %d\n", tmp, size);
	j = 0;
	while (start <= size)
	{
		new[start] = tmp[j];
		//printf("new[%d] = %c tmp[%d] = %c\n", start, new[start], j, tmp[j]);
		start++;
		j++;
	}
	size = ft_strlen(str) - 2;
	while (start < size)
	{
		new[start] = str[i+1];
		//printf("new[%d] = %c str[%d] = %c\n", start, new[start], i + 1, str[i + 1]);
		start++;
		i++;
	}
	new[start] = '\0';
	return (new);
}

// concatenation quand tmp est au depart de la str
char	*ft_retnoneg(int i, char *str, char *tmp, char *new)
{
	int start;
	int	size;
	int	j;

	start = 0;
	j = 0;
	while (start < i - 2)
	{
		new[start] = tmp[start];
		//printf("new[%d] = %c tmp[%d] = %c\n", start, new[start], start, tmp[start]);
		start++;
	}
	size = ft_strlen(str) - 2;
	while (start <= size)
	{
		new[start] = str[i];
	//printf("new[%d] = %c str[%d] = %c\n", start, new[start], i, str[i]);
		start++;
		i++;
	}
	new[start] = '\0';
	return (new);
}

char	*ft_special_cat(char *str, char *tmp, int i, int ret)
{
	char	*new;
	int	start;
	int		size;

	start = 0;
	size = ft_strlen(str) - 2;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	if (ret == -1)
		new = ft_retneg(i, str, tmp, new);
	else
		new = ft_retnoneg(i, str, tmp, new);
	free (str);
	return (new);	
}

char	*ft_cut_quote(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	//size = end - start;
	size = ft_strlen(str);
	i = 0;
	//printf("st = %d en= %d \n", start, end);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (start <= end)
	{
		dest[i] = str[start];
		start++;
		i++;
	}
	while(i < size)
	{
		dest[i] = str[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
