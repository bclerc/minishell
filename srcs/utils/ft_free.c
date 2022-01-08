/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:13:52 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 16:04:24 by asgaulti         ###   ########.fr       */
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
		printf("cmd p %p %s i %d\n", arg->cmds[i], arg->cmds[i], i);
		free(arg->cmds[i]);
		i++;
	}
	if (arg->cmds)
		free(arg->cmds);
}
