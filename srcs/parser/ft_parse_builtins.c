/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/20 16:49:44 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_cd(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;

	j = 0;
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[j]);
	j++;
	if (!cpy[j])
		return (ft_print("\n", -1));
	cmd->msg = ft_strdup(cpy[j]);
	printf("cd : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd = cmd->next;
	return (j);
}

int	ft_parse_builtins(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;

	j = 0;
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[j]);
	j++;
	if (!cpy[j])
		return (ft_print("\n", -1));
	cmd->msg = ft_strdup(cpy[j]);
	printf("builtins : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd = cmd->next;
	return (j);
}

void	ft_std(t_arg *arg, t_cmd *cmd, int i)
{
	if (arg->cmds[i] == "|")
	{
		printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cmd->std = 1;
	}
	else if (arg->cmds[i] == ">")
	{
		printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cmd->std = 2;
	}
	else if (arg->cmds[i] == ">>")
	{
		printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cmd->std = 3;
	}
	else if (arg->cmds[i] == "<")
	{
		printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cmd->std = 4;
	}
	else if (arg->cmds[i] == "<<")
	{
		printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cmd->std = 5;
	}
}
