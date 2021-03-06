/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:50:10 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/20 18:07:35 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_check_spec(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if ((*cmd)->std > 1 && (*cmd)->std <= 5)
	{
		while (*cmd && (*cmd)->next)
		{
			if ((*cmd)->msg == NULL)
				*cmd = (*cmd)->next;
			else if ((*cmd)->msg && (*cmd)->msg[0] == '-')
			{
				tmp->spec = (*cmd)->msg;
				(*cmd)->msg = NULL;
				break ;
			}
			*cmd = (*cmd)->next;
		}
	}
	*cmd = tmp;
	return (*cmd);
}
