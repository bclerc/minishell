/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:55:35 by astrid            #+#    #+#             */
/*   Updated: 2021/12/27 18:32:32 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init arg
// count arg
// stock arg
int	ft_get_arg(char *str, t_arg *arg)
{
	ft_init_arg(arg, str);
	if (ft_quotes(str, arg) == -1)
		return (-1);
	if (ft_count_arg(str, arg) == -1)
		return (-1);
	if (ft_stock_arg(arg, str) == -1)
		return (-1);
	arg->start = 0;
puts("che");
	// if (ft_check_args(arg) == -1)
	// 	return (-1);
	return (0);
}

// determiner le nb d args (en fct des sep | < >)
int	ft_count_arg(char *str, t_arg *arg)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i = ft_increase_quote(str, i);
		if (((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<')) && i != 0)
		{
			arg->count++;
			i+=2;
			if (str[i + 1])
				arg->count++;
		}
		else if (((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|') && i != 0)
		{
			arg->count++;
			if (str[i + 1])
				arg->count++;
		}
		else if ((((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
			|| ((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|'))
			&& i == 0)
			return (ft_print("There is no command here...\n", -1) & -1);
		i++;
	}
	if (i == 0)
		arg->count = 0; // ou return (-1)?
	return (0);
}

// recup args par chaines
// + check args (quotes, no sep)
int	ft_stock_arg(t_arg *arg, char *str)
{
	int		c;
	int		i;
	int		size;
	t_arg	*tmp;

	c = 0;
	i = 0;	
	arg->cmds = malloc(sizeof(char *) * (arg->count + 1));
	if (!arg->cmds)
		return (1);
	tmp = arg;
	size = ft_strlen(str); // pas de +1!!
	while (i < size)
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|'
			|| str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				i = ft_increase_quote(str, i);
				//i++;
			}
			printf("i %d st = %d ch = %c\n", i, arg->start, str[i]);
			arg->cmds[c] = ft_parse_arg(str, i, arg);
			c++;
			i = ft_check_char(str, i, c, arg);
			printf("i2 %d\n", i);
			if (i == -1)
				return (1);
			arg->start = i;
			c++;
		}
		i++;
	}
	if (c != arg->count)
		arg->cmds[c] = ft_nosep(i, str, arg);
	c = 0;
	while (c < arg->count)
	{
	printf("cmd = %s i = %d\n", arg->cmds[c], i);
		c++;
	}
	return (0);
}
/*
int	ft_check_args(t_arg *arg)
{
	int	i;
	int	j;

	i = 0;
	while (i < arg->count)
	{
		j = 0;
		while (arg->cmds[i][j])
		{
			if (arg->cmds[i][j] == '\'')
				arg->count_quote++;
			else if (arg->cmds[i][j] == '"')
				arg->count_quotes++;
			j++;
		}
		if (arg->count_quotes % 2 != 0 || arg->count_quote % 2 != 0)
			return (ft_print("Error : There is an odd number of quotes\n", -1));
		i++;
	}
	return (0);
}
*/

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
		while (str[i != '\''])
			i++;
	}
	return (i);
}
