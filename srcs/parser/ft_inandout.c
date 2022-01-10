/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inandout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:28:55 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/09 19:29:38 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_inout(t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	char	*fd_in;
	char	*msg;
	int		std_in;
	t_cmd	*cpy;

	fd_in = NULL;
	cpy = NULL;
	msg = NULL;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	while (tmp && tmp->previous != NULL)
	{
		while (tmp->previous != NULL && (tmp->previous->std >= 2 && tmp->previous->std <= 5))
		{
			if ((tmp->previous->std == 4 || tmp->previous->std == 5) && !fd_in)
			{
				fd_in = tmp->cmd;
				tmp->cmd = NULL;
				std_in = tmp->previous->std;
				if (tmp->previous->msg)
					msg = tmp->previous->msg;
			}
			else if ((tmp->previous->std == 4 || tmp->previous->std == 5) && fd_in)
				tmp->cmd = NULL;
			tmp = tmp->previous;
		}
		if (tmp->std != 0)
			cmd = tmp;
		if (fd_in)
		{
			tmp = ft_in(fd_in, msg, std_in, tmp, redir);
			if (!tmp)
				return (NULL);
			cpy = tmp;
			while (cpy->next != NULL && (cpy->std >= 2 && cpy->std <= 5))
			{
				if ((cpy->std == 2 || cpy->std == 3) && fd_in)
				{
					tmp->redir->fd_out = cpy->next->cmd;
					cpy->next->cmd = NULL;
					tmp->redir->redir_std_out = cpy->std;
					tmp->redir->next = NULL;
					fd_in = NULL;
				}
				else if ((cpy->std == 2 || cpy->std == 3) && !fd_in)
				{
					if (tmp->redir->redir_msg)
						msg = tmp->redir->redir_msg;
					tmp->redir = ft_out(cpy, tmp->redir, msg);
				}
				cpy = cpy->next;
			}
			//printf("tmp in %s out %s std %d msg %s\n", tmp->redir->fd_in, tmp->redir->fd_out, tmp->redir->redir_std_in, tmp->redir->redir_msg);
		}
		else if (!fd_in)
		{
			redir = NULL;
			tmp->redir = NULL;
			cpy = tmp;
			while (cpy->next != NULL && (cpy->std == 2 || cpy->std == 3))
			{
				tmp->redir = ft_out(cpy, tmp->redir, msg);
				cpy = cpy->next;
			}
			//printf("tmp %p in %s out %s std %d msg %s\n", tmp->redir, tmp->redir->fd_in, tmp->redir->fd_out, tmp->redir->redir_std_out, tmp->redir->redir_msg);
		}
		if (!tmp->previous)
			break ;
		tmp = tmp->previous;
	}
	return (tmp);
}

t_cmd	*ft_in(char *fd_in, char *msg, int std_in, t_cmd *tmp, t_redir *redir)
{
	tmp->redir = malloc(sizeof(t_redir));
	if (!tmp->redir)
		return (NULL);
	ft_init_redir(tmp->redir);
	tmp->redir->fd_in = fd_in;
	tmp->redir->redir_std_in = std_in;
	if (tmp->msg)
		tmp->redir->redir_msg = tmp->msg;
	return (tmp);
}

t_redir	*ft_out(t_cmd *cmd, t_redir *redir, char *msg)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	ft_init_redir(new);
	new->redir_std_out = cmd->std;
	new->fd_out = cmd->next->cmd;
	cmd->next->cmd = NULL;
	if (msg)
		new->redir_msg = msg;
	new->next = NULL;
	// printf("new : %p cmd %s out %s std %d msg %s\n", new, cmd->cmd, new->fd_out, new->redir_std_out, new->redir_msg);
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}
