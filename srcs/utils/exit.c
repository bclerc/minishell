/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:12:23 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 16:47:34 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_env(void)
{
	t_env	*tmp;

	while (g_core->env)
	{
		tmp = g_core->env->next;
		free(g_core->env->value);
		free(g_core->env);
		g_core->env = tmp;
	}
}

void	del_redir(t_redir *redir)
{
	int	i;

	if (redir == NULL)
		return ;
	if (redir->next)
		del_redir(redir->next);
	if (redir->fd_in)
		free(redir->fd_in);
	if (redir->fd_out)
		free(redir->fd_out);
	free(redir);
}

void	del_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->next)
			del_cmd(cmd->next);
		del_redir(cmd->redir);
		if (cmd->msg != NULL)
			free(cmd->msg);
		if (cmd->cmd != NULL)
			free(cmd->cmd);
		cmd->next = NULL;
		cmd->cmd = NULL;
		cmd->msg = NULL;
		cmd->redir = NULL;
		cmd->spec = NULL;
		free(cmd);
	}
}

void	m_exit(t_cmd *cmd, int reason, char *function)
{
	t_redir	redir;
	t_cmd	*tmp;
	int		i;

	del_cmd(cmd);
	cmd = NULL;
	if (reason != M_EXIT_FORK)
		del_env();
	if (reason == M_EXIT_MALLOC_ERROR)
		printf("\nMinishell: Malloc error:\nFunction: %s\n", function);
}
