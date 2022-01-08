/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/08 15:14:38 by asgaulti         ###   ########.fr       */
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
	tmp = *cmd;
	if (ft_get_arg(str, &arg) == -1)
		return (NULL);
	if (ft_init_cmd(cmd, &arg) < 0)
		return (NULL);
	*cmd = ft_get_cmd(&arg, cmd);
	if (!*cmd)
		return (NULL);
	ft_free_arg(&arg);
	return (*cmd);
}
