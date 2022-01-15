/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:13:52 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 11:24:22 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arg(t_arg *arg)
{
	int	i;
	int	c;

	i = 0;
	c = arg->count;
	while (i < c)
	{
		free(arg->cmds[i]);
		i++;
	}
	if (arg->cmds)
		free(arg->cmds);
}
