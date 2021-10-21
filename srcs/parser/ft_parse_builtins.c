/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/21 12:04:00 by astrid           ###   ########.fr       */
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
	{
		printf("cd1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		return (ft_print("\n", -1));
	}
	cmd->msg = ft_strdup(cpy[j]);
	if (!arg->cmds[i + 1])
		cmd->std = 0;
	else if (arg->cmds[i + 1])
		ft_std(arg, cmd, i + 1);
	printf("cd2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
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
	{
		printf("builtins1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		return (ft_print("\n", -1));
	}
	cmd->msg = ft_strdup(cpy[j]);
	if (!arg->cmds[i + 1])
		cmd->std = 0;
	else if (arg->cmds[i + 1])
		ft_std(arg, cmd, i + 1);
	printf("builtins2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd = cmd->next;
	return (j);
}

int	ft_parse_other(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;

	j = 0;
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[j]);
	j++;
	if (!cpy[j])
	{
		printf("other1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		return (ft_print("\n", -1));
	}
	cmd->msg = ft_strdup(cpy[j]);
	if (!arg->cmds[i + 1])
		cmd->std = 0;
	else if (arg->cmds[i + 1])
		ft_std(arg, cmd, i + 1);
	printf("other2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd = cmd->next;
	return (j);
}

void	ft_std(t_arg *arg, t_cmd *cmd, int i)
{
	if (ft_strncmp(arg->cmds[i], "|", ft_strlen(arg->cmds[i])) == 0)
		cmd->std = 1;
	else if (ft_strncmp(arg->cmds[i], ">", ft_strlen(arg->cmds[i])) == 0)
		cmd->std = 2;
	else if (ft_strncmp(arg->cmds[i], ">>", ft_strlen(arg->cmds[i])) == 0)
		cmd->std = 3;
	else if (ft_strncmp(arg->cmds[i], "<", ft_strlen(arg->cmds[i])) == 0)
		cmd->std = 4;
	else if (ft_strncmp(arg->cmds[i], "<<", ft_strlen(arg->cmds[i])) == 0)
		cmd->std = 5;
}
