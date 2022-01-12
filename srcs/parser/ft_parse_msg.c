/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2022/01/12 12:56:04 by bclerc           ###   ########.fr       */
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
		start = ft_strlen(cpy[0]) + 1;
		tmp = ft_other_msg(arg, start, tmp);
	}	
	else if (j == 1 || j == 2)
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
		if (str[arg->pos_i] == '\'' || str[arg->pos_i] == '"')
			str = ft_check_quotes(str, arg, tmp, size);
		if (!str)
			return (NULL);
		arg->pos_i++;
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
	if (!str)
		return (str);
	while (str[i] != '\'')
	{
		if (str[i] == '"')
			arg->count_quotes++;
		i++;
	}
	if (arg->count_quotes % 2 != 0)
		return (ft_print("There is an error with quotes\n", -1), NULL);
	pos_end = i - 1;
	arg->pos_i = i;
	tmp = ft_cut_quote(str, pos_st, pos_end);
	str = ft_check_tmp(tmp, pos_st, str, i);
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
	while (str[i] != '"')
	{
		if (str[i] == '\'')
			arg->count_quote++;
		i++;
	}
	if (arg->count_quote % 2 != 0)
		return (ft_print("There is an error with quotes", -1), NULL);
	pos_end = i - 1;
	arg->pos_i = i;
	tmp = ft_cut_quote(str, pos_st, pos_end);
	str = ft_check_tmp(tmp, pos_st, str, i);
	return (str);
}

char	*ft_check_tmp(char *tmp, int pos_st, char *str, int i)
{
	if (tmp)
	{
		if (pos_st != 1)
			str = ft_special_cat(str, tmp, pos_st - 1, -1);
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
