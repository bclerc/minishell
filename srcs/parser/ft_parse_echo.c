/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/24 15:26:31 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_echo(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;
	int	tmp;

	j = 0;
	tmp = i;
	while (cpy[tmp])
		tmp++;
	cmd->cpy_nb = tmp;
	printf("cpy_nb = %d i = %d\n", cmd->cpy_nb, i);
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
				ft_cpy_msg(arg, cpy, i, j, cmd);
			else if (!cpy[j])
			{
				printf("echo1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
				return (ft_print("\n", -1) & -1);
			}
		}
		else
			ft_cpy_msg(arg, cpy, i, j, cmd);
		printf("cmd_msg = %s\n", cmd->msg);
	}
	printf("j = %d i = %d\n", j, i);
	if (i == arg->count - 1)
		cmd->std = 0;
	else if (i < arg->count)
		ft_std(arg, cmd, i + 1);
	printf("echo2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd->next = NULL;
	return (j);
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