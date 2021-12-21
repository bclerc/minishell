/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:55:35 by astrid            #+#    #+#             */
/*   Updated: 2021/12/21 14:42:18 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init arg
// count arg
// stock arg
int	ft_get_arg(char *str, t_arg *arg)
{
	ft_init_arg(arg, str);
	ft_count_arg(str, arg);
	if (ft_stock_arg(arg, str) == 1)
		return (-1);
	arg->start = 0;
	if (ft_check_args(arg) == -1)
		return (-1);
	return (0);
}

// determiner le nb d args (en fct des sep | < >)
void	ft_count_arg(char *str, t_arg *arg)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			arg->count++;
			i++;
			if (str[i])
				arg->count++;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			arg->count++;
			if (str[i + 1])
				arg->count++;
		}	
		i++;
	}
	if (i == 0)
		arg->count = 0;
}

// recup args par chaines
// + check args (quotes, no sep)
int	ft_stock_arg(t_arg *arg, char *str)
{
	int		c;
	int		i;

	c = 0;
	i = -1;
	arg->cmds = malloc(sizeof(char *) * (arg->count + 1));
	if (!arg->cmds)
		return (1);
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			arg->cmds[c] = ft_parse_arg(str, i, arg);
			c++;
			if (ft_check_char(str, i, c, arg) == -1)
				return (1);
			else
				i = ft_check_char(str, i, c, arg);
			arg->start = i;
			c++;
		}
	}
	if (c != arg->count)
		arg->cmds[c] = ft_nosep(i, str, arg);
	return (0);
}

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
