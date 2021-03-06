/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:55:35 by astrid            #+#    #+#             */
/*   Updated: 2022/01/14 10:56:44 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init arg
// count arg
// stock arg
int	ft_get_arg(char *str, t_arg *arg)
{
	int	ret;

	ft_init_arg(arg, str);
	ret = ft_no(str);
	if (ret != 0)
	{
		if (ret == -1)
			return (ft_print("syntax error\n", -1) & -1);
		else if (ret == -2)
			return (ft_print("syntax error near unexpected token `newline'\n",
					-1) & -1);
	}
	if (ft_quotes(str, arg) == -1)
		return (-1);
	if (ft_count_arg(str, arg) == -1)
		return (-1);
	if (ft_stock_arg(arg, str) == -1)
		return (-1);
	arg->start = 0;
	return (0);
}

// determiner le nb d args (en fct des sep | < >)
int	ft_count_arg(char *str, t_arg *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	i = ft_begin_chevron(str, i, size, arg);
	if (i < 0)
		return (-1);
	while (i < size)
	{
		i = ft_increase_quote(str, i);
		if (((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')) && i != 0)
			i = ft_count1(str, i, arg);
		else if (i != 0 && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|'))
			ft_count2(str, i, arg);
		i++;
	}
	if (i == 0)
		arg->count = 0;
	return (0);
}

// recup args par chaines
// + check args (quotes, no sep)
int	ft_stock_arg(t_arg *arg, char *str)
{
	arg->cmds = malloc(sizeof(char *) * (arg->count));
	if (!arg->cmds)
		return (1);
	// arg->i = ft_special_chev(arg, str);
	if (arg->i < 0)
		return (1);
	while (arg->i < ft_strlen(str))
	{
		arg->i = ft_stock_i(str, arg->i);
		if (str[arg->i] == '<' || str[arg->i] == '>' || str[arg->i] == '|')
		{
			arg->cmds[arg->c] = ft_parse_arg(str, arg->i - 1, arg);
			if (!arg->cmds[arg->c])
				return (1);
			arg->c++;
			arg->i = ft_check_char(str, arg->i, arg->c, arg);
			if (arg->i == -1)
				return (1);
			ft_util_stockarg(arg);
		}
		arg->i++;
	}
	if (arg->c != arg->count)
		arg->cmds[arg->c] = ft_nosep(arg->i, str, arg);
	return (0);
}

int	ft_quotes(char *str, t_arg *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (str[i] == '\'')
			arg->count_quote++;
		else if (str[i] == '"')
			arg->count_quotes++;
		i++;
	}
	if (arg->count_quotes % 2 != 0 || arg->count_quote % 2 != 0)
		return (ft_print("Error : There is an odd number of quotes\n", -1));
	return (0);
}

int	ft_increase_quote(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}
