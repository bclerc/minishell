/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:50:10 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/17 14:44:23 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_check_spec(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if ((*cmd)->std > 1 && (*cmd)->std <= 5 && !(*cmd)->msg)
	{
		while (*cmd && (*cmd)->next != NULL)
		{
			if ((*cmd)->msg == NULL)
				
			*cmd = (*cmd)->next;
			printf("cmd = %s msg = %s \n", (*cmd)->cmd, (*cmd)->msg);
			if ((*cmd)->msg[0] == '-')
			{
				puts ("che");
				tmp->msg = (*cmd)->msg;
				(*cmd)->msg = NULL;
				break;
			}
			//*cmd = (*cmd)->next;
		}
	}
	*cmd = tmp;
	return (*cmd);
}
