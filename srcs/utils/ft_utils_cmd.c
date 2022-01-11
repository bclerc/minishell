/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:13:16 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 12:49:08 by bclerc           ###   ########.fr       */
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
	char *tmp;
	tmp = cpy;
	cpy = ft_strsub(tmp, 1, ft_strlen(tmp) - 2);
	free(tmp);
	if (!cpy)
		return (NULL);
	arg->q = 1;
	return (cpy);
}
