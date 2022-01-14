/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2022/01/14 14:47:12 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == ' ')
		size = ft_strlen(str) - 1;
	else
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

	pos_st = arg->pos_i + 1;
	i = ft_i_quote(i, arg, str);
	pos_end = i - 1;
	if (ft_strncmp(arg->cmds[arg->i_cpy], "export", 6) != 0)
	{
		tmp = ft_cut_quote(str, pos_st, pos_end);
		str = ft_check_tmp(tmp, pos_st, str, i);
	}
	else if (ft_strncmp(arg->cmds[arg->i_cpy], "export", 6) == 0)
	{
		tmp = ft_cut_quote_export(str, pos_st, pos_end);
		if (pos_st != 1)
			str = ft_special_cat_export(str, tmp, pos_st - 1, -1);
		else
			str = ft_special_cat_export(str, tmp, i + 1, 0);
		if (!str)
			return (NULL);
		free (tmp);
	}
	return (str);
}

char	*ft_dq(t_arg *arg, char *str, char *tmp)
{
	int		pos_st;
	int		pos_end;
	int		i;

	pos_st = arg->pos_i + 1;
	i = ft_i_quotes(i, arg, str);
	pos_end = i - 1;
	if (ft_strncmp(arg->cmds[arg->i_cpy], "export", 6) != 0)
	{
		tmp = ft_cut_quote(str, pos_st, pos_end);
		str = ft_check_tmp(tmp, pos_st, str, i);
	}
	else if (ft_strncmp(arg->cmds[arg->i_cpy], "export", 6) == 0)
	{
		tmp = ft_cut_quote_export(str, pos_st, pos_end);
		if (pos_st != 1)
			str = ft_special_cat_export(str, tmp, pos_st - 1, -1);
		else
			str = ft_special_cat_export(str, tmp, i + 1, 0);
		if (!str)
			return (NULL);
		free (tmp);
	}	
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
