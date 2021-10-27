/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/27 09:27:43 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, char **envp)
{
	int		i;
	t_arg	arg;
	t_cmd	cmd;
	
	i = 0;
	if (ft_get_arg(str, &arg) == -1)
		return (-1);
	// while (arg.cmds[i])
	//  	i++;
	// printf("i = %d\n", i);
	if (ft_init_cmd(&cmd, &arg) < 0)
		return (-1);
	i = 0;
	if (ft_get_cmd(&arg, &cmd) == -1)
		return (-1);
	// while (arg.cmds[i])
	// {
	// 	puts("che");
	// 	ft_get_cmd(&arg, &cmd);
	// 	i++;	
	// }
	return (&cmd);
}
