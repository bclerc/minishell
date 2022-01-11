/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 12:09:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, t_cmd **cmd)
{
	int		i;
	t_arg	arg;

	i = 0;
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
