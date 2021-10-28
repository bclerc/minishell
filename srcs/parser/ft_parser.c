/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/28 12:35:34 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, char **envp, t_cmd **cmd)
{
	int		i;
	t_arg	arg;
	//t_cmd	cmd;
	
	i = 0;
	*cmd = NULL;
	if (ft_get_arg(str, &arg) == -1)
		return (NULL);
	// while (arg.cmds[i])
	//  	i++;
	// printf("i = %d\n", i);
	if (ft_init_cmd(cmd, &arg) < 0)
		return (NULL);
	i = 0;
	*cmd = ft_get_cmd(&arg, cmd);
	if (!*cmd)
		{
			puts("che2");
			return (NULL);
		}
	// while (arg.cmds[i])
	// {
	// 	puts("che");
	// 	ft_get_cmd(&arg, &cmd);
	// 	i++;	
	// }
	return (*cmd);
}
