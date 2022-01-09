/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:12:23 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/09 19:30:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_env(void)
{
	t_env	*tmp;

	while (core->env)
	{
		tmp = core->env->next;
		free(core->env->value);
		free(core->env);
		core->env = tmp;
	}
}

// del tout le maillon, pas uniquement msg et spec a priori
void	del_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		del_cmd(cmd->next);
		if (cmd->msg != NULL)
		{
			ft_bzero(cmd->msg, ft_strlen(cmd->msg));
			free(cmd->msg);
		}
		if (cmd->spec != NULL)
			free(cmd->spec);
		// if (cmd->cmd)
		// 	free(cmd->cmd);
		free(cmd);
	}
}

void del_redir(t_redir *redir)
{
	int i;

	if (redir == NULL)
		return ;
	if (!redir->next)
	{
		if (redir->fd_in)
			free(redir->fd_in);;
		if (redir->fd_out)
			free(redir->fd_out);
		free(redir);
	}
	else
	{	
		if (redir->next)
		{
			del_redir(redir->next);
			if (redir->fd_in)
				free(redir->fd_in);;
			if (redir->fd_out)
				free(redir->fd_out);
			if (redir->next)
				free(redir);
		}
	}
}

void	m_exit(t_cmd *cmd, int reason, char *function)
{
	t_redir	*redir;
	t_cmd	*tmp;
	int		i;

	del_redir(cmd->redir);
	del_cmd(cmd);
	cmd = NULL;
	if (reason != M_EXIT_FORK)
		del_env();
	if (reason == M_EXIT_MALLOC_ERROR)
		printf("\nMinishell: Malloc error:\nFunction: %s\n", function);
}
