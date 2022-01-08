/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:13:16 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/07 13:22:09 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_i(t_arg *arg, int i)
{
	if ((ft_check_redir(arg, i) == 1 && (i + 1 < arg->count))
		|| (ft_check_redir(arg, i) == 2 && (i + 1 < arg->count)))
		i++;
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
