/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/16 14:51:55 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, t_cmd **cmd)
{
	int		i;
	t_arg	arg;
	t_cmd	*tmp;

	i = 0;
	//*cmd = NULL;
	tmp = *cmd;
	//printf("&tmp = %p p = %p\n", tmp, *cmd);
	if (ft_get_arg(str, &arg) == -1)
		return (NULL);
	if (ft_init_cmd(cmd, &arg) < 0)
		return (NULL);
	*cmd = ft_get_cmd(&arg, cmd);
	//	printf("checkcmd : p = %p ptmp = %p, cmd = %s, spec = %s, msg = %s, std = %d in = %s out = %s\n", (*cmd), tmp, (*cmd)->cmd, (*cmd)->spec, (*cmd)->msg, (*cmd)->std, (*cmd)->fd_in, (*cmd)->fd_out);
	
	
	//printf("checkcmd : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d in = %s out = %s\n", tmp->nb, tmp->cmd, tmp->spec, tmp->msg, tmp->std, tmp->fd_in, tmp->fd_out);
	// while (tmp->next != NULL)
	// {
	// 	tmp = tmp->next;
	// }
	if (!*cmd)
		return (NULL);
	return (*cmd);
}
