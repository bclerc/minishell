/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/29 08:52:19 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, char **envp, t_cmd **cmd)
{
	int		i;
	t_arg	arg;
	
	i = 0;
	*cmd = NULL;
	if (ft_get_arg(str, &arg) == -1)
		return (NULL);
	if (ft_init_cmd(cmd, &arg) < 0)
		return (NULL);
	i = 0;
	*cmd = ft_get_cmd(&arg, cmd);
	if (!*cmd)
		return (NULL);
	return (*cmd);
}
