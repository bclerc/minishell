/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:30:13 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/06 11:44:28 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count1(char *str, int i, t_arg *arg)
{
	arg->count++;
	i += 2;
	if (str[i + 1])
		arg->count++;
	return (i);
}

void	ft_count2(char *str, int i, t_arg *arg)
{
	arg->count++;
	if (str[i + 1])
		arg->count++;
}

int	ft_stock_i(char *str, int i)
{
	while (str[i] != '<' && str[i] != '>' && str[i] != '|'
		&& str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			i = ft_increase_quote(str, i);
		i++;
	}
	return (i);
}
