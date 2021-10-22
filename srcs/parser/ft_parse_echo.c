/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/22 12:09:24 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_echo(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;

	j = 0;
	puts ("che");
	// cmd = malloc(sizeof(t_cmd));
	// if (!cmd)
	// 	return (-1);
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[j]);
	//printf("arg = %p cmd = %p\n", &arg->cmds[i], &cmd->arg);
	j++;
	if (cpy[j])
	{
		if (ft_strncmp(cpy[j], "-n", 2) == 0)
		{
			if (ft_check_n(cpy, cmd, j) == -1 )
				return (-1);
			j++;
			if (cpy[j])
				ft_echo_msg(arg, cpy, j, cmd);
			else if (!cpy[j])
			{
				printf("echo1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
				return (ft_print("\n", -1) & -1);
			}
		}
		else
			j = ft_echo_msg(arg, cpy, j, cmd);
	}
	if (!arg->cmds[i + 1])
		cmd->std = 0;
	else if (arg->cmds[i + 1])
		ft_std(arg, cmd, i + 1);
	printf("echo2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd->next = NULL;
	return (j);
}

int	ft_echo_msg(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	printf("cpy[%d] = %s\n", i, cpy[i]);
	if (!cpy[i])
		return (ft_print("\n", -1));
	//cpy[i] = ft_parse_msg(arg, cpy, i);
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