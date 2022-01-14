/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_arg2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:08 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/14 10:56:25 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_begin_chevron(char *str, int i, int size, t_arg *arg)
{
	if (str[i] == '|' && i == 0)
		return (-1);
	else if (((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<')) && i == 0)
	{
		while (i++ < size)
		{
			if (str[i] >= 32 && str[i] <= 126)
			{
				arg->count += 1;
				return (1);
			}
		}
		return (-1);
	}
	else if (((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>')) && i == 0)
		return (ft_begin_util(str, i, size, arg));
	return (0);
}

int	ft_begin_util(char *str, int i, int size, t_arg *arg)
{
	{
		i++;
		while (i++ < size)
		{
			if (str[i] >= 32 && str[i] <= 126)
			{
				arg->count += 1;
				return (2);
			}
		}
	}
	return (-1);
}

int	ft_special_chev(t_arg *arg, char *str)
{
	if (str[arg->i] == '<' || str[arg->i] == '>')
	{
//		printf("i0 = %d cou %d cmd[%d] %s\n", arg->i, arg->count, arg->c, arg->cmds[arg->c]);
		arg->i = ft_check_char(str, arg->i, arg->c, arg);
		if (arg->i == -1)
			return (-1);
		arg->c++;
		arg->start = arg->i;
		while (str[arg->i] && str[arg->i] != '<' && str[arg->i] != '>')
			arg->i++;
		arg->cmds[arg->c] = ft_parse_arg(str, arg->i, arg);
		if (!arg->cmds[arg->c])
			return (1);
		arg->c++;
		if (arg->c < arg->count)
		{
			while (arg->c < arg->count)
			{
				if (str[arg->i] == '<' || str[arg->i] == '>')
				{
					arg->i = ft_check_char(str, arg->i, arg->c, arg);
					if (arg->i == -1)
						return (1);
					arg->start = arg->i;
					while (str[arg->i] && str[arg->i] != '<' && str[arg->i] != '>')
						arg->i++;
					if (arg->c < arg->count - 1)
						arg->c++;
					arg->cmds[arg->c] = ft_parse_arg(str, arg->i, arg);
					arg->c++;
				}
				arg->i++;
			}
			return (arg->i);
		}
	}
	return (0);
}

void	ft_util_stockarg(t_arg *arg)
{
	arg->start = arg->i;
	if (arg->c < arg->count - 1)
		arg->c++;
}
