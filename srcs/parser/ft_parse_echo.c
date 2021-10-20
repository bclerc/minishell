/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/20 08:20:20 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_echo(char **cpy, int i, t_cmd *cmd)
{
	//ft_bzero(cmd, sizeof(t_cmd));
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[i]);
	//printf("arg = %p cmd = %p\n", &arg->cmds[i], &cmd->arg);
	i++;
	if (cpy[i])
	{
		if (ft_strncmp(cpy[i], "-n", 2) == 0)
		{
			if (ft_check_n(cpy, cmd, i) == -1 )
				return (-1);
			i++;
			if (cpy[i])
				ft_echo_msg(cpy, i, cmd);
			else if (!cpy[i])
				return (ft_print("\n", -1) & -1);
		}
		else
			i = ft_echo_msg(cpy, i, cmd);
		//printf("cmds[%i] = %s\n", i + 1, arg->cmds[i + 1]);
		// if (i == -1)
		// 	return (-1);
	}
	if (!cpy[i])
		cmd->std = 1; // pour executer de suite?
	printf("nb = %d, cmd = %s, spec = %s, msg = %s, std = %d i = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, i);
	cmd = cmd->next;
	return (i);
}

int	ft_echo_msg(char **cpy, int i, t_cmd *cmd)
{
	if (!cpy[i])
		return (ft_print("\n", -1));
	cmd->msg = ft_strdup(cpy[i]);
	i++;
	//printf("i_msg= %d\n", i);
	return (i);
}

int	ft_check_n(char **cpy, t_cmd *cmd, int i)
{
	int j;

	j = 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] != 'n')
			ft_print("Error in specification\n", -1);
		j++;
	}
	cmd->spec = "-n";
	return (0);
}