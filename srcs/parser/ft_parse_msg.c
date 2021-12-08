/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/12/08 17:48:34 by asgaulti         ###   ########.fr       */
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
		//printf("cpy = %s\n", cpy[1]);
		start = ft_strlen(cpy[0]) + 1;
		//printf("st = %d\n", start);
		tmp = ft_other_msg(arg, start, tmp);
		//tmp = cpy[1]; // ok MAIS seulement s'il n'y a qu'un seul msg
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
		if (!str)
			return (NULL);
		arg->pos_i++;
		//printf("i = %d size = %d str = %s\n", arg->pos_i, size, str);
	}
	return (str);
}

char	*ft_sq(t_arg *arg, char *str, char *tmp)
{
	int		pos_st;
	int		pos_end;
	int		i;
	
	i = arg->pos_i;
	pos_st = i + 1;
	i++;
	while (str[i] != '\''/* && str[i]*/)
	{
		if (str[i] == '"')
			arg->count_quotes++;
		i++;
	}
	if (arg->count_quotes % 2 != 0)
	{
		ft_print("There is an error with quotes\n", -1);
		return (NULL);
	}
	pos_end = i - 1;
	arg->pos_i = i;
	tmp = ft_cut_quote(str, pos_st, pos_end);
	if (tmp)
	{
		if (pos_st != 1)
			str = ft_special_cat(str, tmp, pos_st - 1, -1);
		else
			str = ft_special_cat(str, tmp, i + 1, 0); // i + 1 ne marche pas tjrs : pb des espaces dans cas particuliers
		// ex : echo " " 'lol' un espace disparait
		free (tmp);	
	}
	else if (!tmp)
	{
		str = ft_special_cat(str, tmp, i, 0);
		free (tmp);	
	}
	//printf("str1 = %s\n", str);
	return (str);
}

char	*ft_dq(t_arg *arg, char *str, char *tmp)
{
	int		pos_st;
	int		pos_end;
	int		i;
	
	//printf("str = %s pos_i = %d \n", str, arg->pos_i);
	i = arg->pos_i;
	pos_st = i + 1;
	i++;
	while (str[i] != '"'/* && str[i]*/)
	{
		if (str[i] == '\'')
			arg->count_quote++;
		i++;
	}
	if (arg->count_quote % 2 != 0)
	{
		ft_print("There is an error with quotes", -1);
		return (NULL);
	}
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
	//printf("str2 = %s\n", str);
	return (str);
}
