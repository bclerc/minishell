/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:12:23 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:58:53 by bclerc           ###   ########.fr       */
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

void	m_exit(t_cmd *cmd, int reason, char *function)
{
	t_redir	*redir;
	t_cmd	*tmp;
	int		i;

	redir = cmd->redir;
	while (cmd)
	{
		free(cmd->msg);
		if (cmd->spec)
			free(cmd->spec);
		tmp = cmd->next;
		cmd = tmp;
	}
	if (cmd)
		free(cmd);
	cmd = NULL;
	if (reason != M_EXIT_FORK)
		del_env();
	if (reason == M_EXIT_MALLOC_ERROR)
		printf("\nMinishell: Malloc error:\nFunction: %s\n", function);
}
