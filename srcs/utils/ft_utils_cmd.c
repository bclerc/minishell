/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:13:16 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/31 11:26:46 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_i(t_arg *arg, int i)
{
	if ((ft_check_redir(arg, i) == 1 && (i + 1 < arg->count))
		|| (ft_check_redir(arg, i) == 2 && (i + 1 < arg->count)))
		i ++;
	return (i);
}

char	*ft_cpy0(char *cpy, t_arg *arg)
{
	cpy = ft_strsub(cpy, 1, ft_strlen(cpy) - 2);
	if (!cpy)
		return (NULL);
	arg->q = 1;
	return (cpy);
}

int	ft_check_chevron(char *str, int i, int c, t_arg *arg)
{
	ft_char(arg, c, '>', 2);
	i++;
	return (i);
}
