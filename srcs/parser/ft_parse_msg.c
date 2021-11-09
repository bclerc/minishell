/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/11/09 10:55:21 by astrid           ###   ########.fr       */
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
	else if (j == 1)
		tmp = ft_which_nb(start, tmp, arg);
	else if (j == 2)
		tmp = ft_which_nb(start, tmp, arg);
	return (tmp);
}

//nettoyer str des quotes en trop
char	*ft_parse_msg(char *str, t_arg *arg)
{
	int		size;
	char	*tmp;

	size = ft_strlen(str);
	arg->pos_i = 0;
	tmp = NULL;
//printf("cpy = %s tmp = %s\n", str, tmp);
	while (arg->pos_i < size)
	{
		if (str[arg->pos_i] == '\'')
		{
			str = ft_sq(arg, str, tmp);
			arg->pos_i -= 2;
			size -= 2;
		}
		else if (str[arg->pos_i] == '"')
		{
			str = ft_dq(arg, str, tmp);
			arg->pos_i -= 2;
			size -= 2;
		}
		arg->pos_i++;
		//printf("i = %d size = %d str = %s\n", arg->pos_i, size, str);
	}
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


// grand mystere : a l'impression dans la fct ca ecrit n'imp mais ca renvoie la bonne chaine a la fin!!!
char	*ft_special_cat(char *str, char *tmp, int i, int ret)
{
	char	*new;
	int 	start;
	int		size;
	int		j;

	start = 0;
	//printf("size = %d\n", size);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	if (ret == -1)
	{
		puts("che1");
		while (start < i)
		{
		new[start] = str[start];
		printf("new[%d] = %c str[%d] = %c\n", start, new[start], start, str[start]);
		start++;
		}
		size = ft_strlen(tmp) + start;
		printf("tmp = %s s = %d\n", tmp, size);
		j = 0;
		while (start <= size)
		{
		new[start] = tmp[j];
	printf("new[%d] = %c tmp[%d] = %c\n", start, new[start], j, tmp[j]);
		start++;
		j++;
		}
		size = ft_strlen(str) - 2;
		while (start < size)
		{
		new[start] = str[i+1];
	printf("new[%d] = %c str[%d] = %c\n", start, new[start], i + 1, str[i + 1]);
		start++;
		i++;
		}
	}
	else
	{
		puts("che2");
		while (start < i - 2)
		{
		new[start] = tmp[start];
		printf("new[%d] = %c tmp[%d] = %c\n", start, new[start], start, tmp[start]);
		start++;
		}
		size = ft_strlen(str) - 2;
		while (start <= size)
		{
		new[start] = str[i];
	printf("new[%d] = %c str[%d] = %c\n", start, new[start], i, str[i]);
		start++;
		i++;
		}
	}
	new[start] = '\0';
	free (str);
	return (new);	
}

char	*ft_sq(t_arg *arg, char *str, char *tmp)
{
	int		pos_st;
	int		pos_end;
	int		i;
	
	i = arg->pos_i;
	pos_st = i + 1;
	i++;
	while (str[i] != '\'' && str[i])
		i++;
	pos_end = i - 1;
	arg->pos_i = i;
	tmp = ft_cut_quote(str, pos_st, pos_end);
	if (tmp)
	{
		//printf("st = %d\n", pos_st);
		if (pos_st != 1)
			str = ft_special_cat(str, tmp, pos_st - 1, -1);
		// regarder ou est le debut de la chaine, pour prendre en compte le début si pas de quotes
		else
			str = ft_special_cat(str, tmp, i + 1, 0); // i + 1 ne marche pas tjrs : pb des espaces dans cas particuliers
		// ex : echo " " 'lol' un espace disparait
		//printf("str = %s\n", str);
		// attention : après il faudra voir les cas ou il y a kk chose avant sans ''
		free (tmp);	
	}
	else if (!tmp)
	{
		str = ft_special_cat(str, tmp, i, 0);
		free (tmp);	
	}
	return (str);
}

char	*ft_dq(t_arg *arg, char *str, char *tmp)
{
	int		pos_st;
	int		pos_end;
	int		i;
	
	i = arg->pos_i;
	pos_st = i + 1;
	i++;
	while (str[i] != '"' && str[i])
		i++;
	pos_end = i - 1;
	arg->pos_i = i;
	tmp = ft_cut_quote(str, pos_st, pos_end);
	if (tmp)
	{
		if (pos_st != 1)
			str = ft_special_cat(str, tmp, pos_st - 1, -1);
		// regarder ou est le debut de la chaine, pour prendre en compte le début si pas de quotes
		else
			str = ft_special_cat(str, tmp, i + 1, 0);
		free (tmp);	
	}
	else if (!tmp)
	{
		str = ft_special_cat(str, tmp, i, 0);
		free (tmp);	
	}
	return (str);
}