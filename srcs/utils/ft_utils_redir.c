/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 11:52:29 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/04 16:16:53 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exist(t_cmd *tmp)
{
	int	exist;

	exist = 0;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->std == 4 || tmp->std == 5)
		{
			if (!exist)
				exist = 1;
			else if (exist == 2)
				exist = 3;				
		}
		else if (tmp->std == 2 || tmp->std == 3)
		{
			if (!exist)
				exist = 2;
			else if (exist == 1)
				exist = 3;				
		}
		tmp = tmp->next;
	}
	return (exist);
}
