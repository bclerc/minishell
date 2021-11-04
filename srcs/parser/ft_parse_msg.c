/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/11/04 16:55:28 by astrid           ###   ########.fr       */
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

char	*ft_parse_msg(char *str, char *tmp, t_arg *arg)
{
	int		pos_st;
	int		pos_end;
	//int		size;
	int		i;

	//size = ft_strlen(cpy);
	i = 0;
printf("cpy[%d] = %s tmp = %s\n", i, str, tmp);
	while (str[i])
	{
		if (str[i] == '\'') // faire ensuite un else if avec "
		{
			pos_st = i + 1;
			i++;
			while (str[i] != '\'')
			{
			printf ("c = %c i = %d\n", str[i], i);
				i++;
			}	
			pos_end = i - 1;
			tmp = ft_cut_quote(str, pos_st, pos_end);
			printf("tmp = %s\n", tmp);
			i -= 2;
			free (tmp);
		}
		i++;
	}
	return (tmp);
}

char	*ft_cut_quote(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = end - start;
	i = 0;
	printf("st = %d en= %d \n", start, end);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = str[start];
		start++;
		i++;
	}
	return (dest);
}
