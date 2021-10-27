/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/27 09:50:13 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	ft_launch_parser(char *str, char **envp)
{
	int		i;
	t_arg	arg;
	t_cmd	cmd;
	
	i = 0;
	if (ft_get_arg(str, &arg) == -1)
		return ;
	// while (arg.cmds[i])
	//  	i++;
	// printf("i = %d\n", i);
	if (ft_init_cmd(&cmd, &arg) < 0)
		return ;
	i = 0;
	if (ft_get_cmd(&arg, &cmd) == -1)
		return ;
	// while (arg.cmds[i])
	// {
	// 	puts("che");
	// 	ft_get_cmd(&arg, &cmd);
	// 	i++;	
	// }
	return (cmd);
}
