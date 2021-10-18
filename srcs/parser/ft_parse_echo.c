/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 15:54:54 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_echo(t_arg *arg, t_cmd *cmd, int i)
{
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->cmd = ft_strdup(arg->cmds[i]);
	//printf("arg = %p cmd = %p\n", &arg->cmds[i], &cmd->arg);
	if (arg->cmds[i + 1])
	{
		if (ft_strncmp(arg->cmds[i + 1], "-n", 2) == 0)
		{
			if (ft_check_n(arg, cmd, i + 1) == -1 )
				return (-1);
			//printf("msg= %s\n", cmd->spec);
			i++;
			if (arg->cmds[i + 1])
				return (i = ft_echo_msg(arg, cmd, i));
			if (!arg->cmds[i + 1])
				return (ft_print("Error : There is no message\n", -1) & -1);
		}
		else
			i = ft_echo_msg(arg, cmd, i + 1);
		//printf("cmds[%i] = %s\n", i + 1, arg->cmds[i + 1]);
		if (i == -1)
			return (-1);
	}
	if (!arg->cmds[i])
		cmd->std = 1; // pour executer de suite?
	return (i);
}

// 
int	ft_echo_msg(t_arg *arg, t_cmd *cmd, int i)
{
	if (!arg->cmds[i])
		return (ft_print("Error : There is no message\n", -1));
	cmd->msg = ft_strdup(arg->cmds[i]);
	i++;
	//printf("i_msg= %d\n", i);
	return (i);
}

int	ft_check_n(t_arg *arg, t_cmd *cmd, int i)
{
	int j;

	j = 1;
	while (arg->cmds[i][j])
	{
		if (arg->cmds[i][j] != 'n')
			ft_print("Error in specification\n", -1);
		j++;
	}
	cmd->spec = "-n";
	return (0);
}