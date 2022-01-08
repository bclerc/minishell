/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:13:52 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 15:08:24 by asgaulti         ###   ########.fr       */
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
	free(arg->cmds);
}
