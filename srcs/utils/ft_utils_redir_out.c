/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:14:35 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 16:37:33 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_fillout(t_cmd *tmp, t_redir *redir)
{
	t_cmd	*cmd;

	while (tmp && tmp->next != NULL)
	{
		if (tmp->std == 2 || tmp->std == 3)
		{
			cmd = tmp;
			tmp = tmp->next;
			while (tmp->prev->std == 2 || tmp->prev->std == 3)
			{
				cmd->redir = ft_create_out(tmp, cmd->redir);
				if (!cmd->redir)
					return (NULL);
				if (!tmp->next)
					break ;
				if (tmp->std != 2 && tmp->std != 3)
					break ;
				tmp = tmp->next;
			}
			tmp = cmd;
		}
		if (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

t_redir	*ft_create_out(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	printf("MALLOC\n");
	if (!new)
		return (0);
	ft_init_redir(new);
	ft_util_out(new, cmd);
	if (cmd->prev->msg)
	{
		new->redir_msg = cmd->prev->msg;
		if (cmd->std == 2 || cmd->std == 3)
			cmd->msg = cmd->prev->msg;
	}
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}

void	ft_util_out(t_redir *new, t_cmd *cmd)
{
	new->redir_std_out = cmd->prev->std;
	cmd->prev->std = 0;
	new->fd_out = cmd->cmd;
	cmd->cmd = NULL;
}
