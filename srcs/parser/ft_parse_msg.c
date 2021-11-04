/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/11/04 21:08:06 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// trouver le msg ds cpy (non splité) et le copier dans tmp
char	*ft_search_msg(char **cpy, int j, t_arg *arg, char *tmp)
{
	int		start;
	
	start = ft_which_cmd(cpy);
	if (start == 7)
	{
		//printf("%s\n", cpy[0]);
		start = ft_strlen(cpy[0]);
		tmp = ft_other_msg(arg, start, tmp);
	}	
	if (j == 1)
		tmp = ft_which_nb(start, tmp, arg);
	else if (j == 2)
	{
		start = 8;
		tmp = ft_msg(arg, start, tmp);
	}
	return (tmp);
}

char	*ft_parse_msg(char *str, t_arg *arg)
{
	int		pos_st;
	int		pos_end;
	//int		size;
	int		i;
	char	*tmp;

	//size = ft_strlen(cpy);
	i = 0;
	tmp = NULL;
printf("cpy = %s tmp = %s\n", str, tmp);
	while (str[i])
	{
		if (str[i] == '\'') // faire ensuite un else if avec "
		{
			pos_st = i + 1;
			i++;
			while (str[i] != '\'' && str[i])
			{
			//printf ("c = %c i = %d\n", str[i], i);
				i++;
			}	
			pos_end = i - 1;
			tmp = ft_cut_quote(str, pos_st, pos_end);
			printf("tmp = %s\n", tmp);
			if (tmp)
			{
				str = ft_special_cat(str, tmp, i + 1);
				printf("str = %s\n", str);
				// attention : après il faudra voir les cas ou il y a kk chose avant sans ''
				free (tmp);	
			}
			i -= 2;
		}
		i++;
	}
	//str[i] = '\n'; // a ajouter? ou deja fait si on concatene?
	return (str);
}

char	*ft_cut_quote(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = end - start;
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
	dest[i] = '\0';
	return (dest);
}

char	*ft_special_cat(char *str, char *tmp, int i)
{
	char	*new;
	int 	start;
	int		size;

	start = 0;
	size = ft_strlen(str) - 2;
	printf("size = %d\n", size);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (start < i - 2)
	{
		printf("new[%d] = %c tmp[%d] = %c\n", start, new[start], start, tmp[start]);
		new[start] = tmp[start];
		start++;
	}
	while (start <= size)
	{
	printf("new[%d] = %c str[%d] = %c\n", start, new[start], i, str[i]);
		new[start] = str[i];
		start++;
		i++;
	}
	new[start] = '\0';
	free (str);
	return (new);	
}
