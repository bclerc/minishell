/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:05:38 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 17:39:43 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_cmd(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

t_cmd	*fill_dup(t_cmd *new, t_cmd *cmd)
{
	if (cmd->msg)
		new->msg = ft_strdup(cmd->msg);
	else
		new->msg = NULL;
	new->cmd = strdup(cmd->cmd);
	new->spec = cmd->spec;
	new->redir = cmd->redir;
	new->std = cmd->std;
	new->builtin = cmd->builtin;
	new->next = NULL;
	return (new);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->msg)
	{
		free(cmd->msg);
		cmd->msg = NULL;
	}
	if (cmd->cmd)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	free(cmd);
	cmd = NULL;
}

t_cmd	*dupp_cmd(t_cmd *cmd)
{
	t_cmd	*ret;
	t_cmd	*new;
	t_cmd	*next;

	ret = NULL;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->cmd != NULL)
		{
			new = (t_cmd *)malloc(sizeof(t_cmd));
			new = fill_dup(new, cmd);
			if (!ret)
				ret = new;
			else
				add_cmd(ret, new);
			free_cmd(cmd);
		}
		else
			free(cmd);
		cmd = next;
	}
	return (ret);
}
