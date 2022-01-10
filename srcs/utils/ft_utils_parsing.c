/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:41:17 by user42            #+#    #+#             */
/*   Updated: 2022/01/09 14:46:59 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sep(t_arg *arg, int i, char c, int count)
{
	int	z;

	z = 0;
	while (z < count)
	{
		arg->cmds[i] = &c;
		z++;
	}
	return (arg->cmds[i]);
}

char	*ft_check_quotes(char *str, t_arg *arg, char *tmp, int size)
{
	if (str[arg->pos_i] == '\'')
	{
		str = ft_sq(arg, str, tmp);
		if (!str)
			return (NULL);
		arg->pos_i -= 2;
		size -= 2;
	}
	else if (str[arg->pos_i] == '"')
	{
		str = ft_dq(arg, str, tmp);
		if (!str)
			return (NULL);
		arg->pos_i -= 2;
		size -= 2;
	}
	return (str);
}
