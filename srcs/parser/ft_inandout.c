/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inandout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:28:55 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 16:09:02 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_inout(t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	t_data	*data;

	data = ft_init_data(data);
	if (!data)
		return (NULL);
	while (tmp && tmp->prev != NULL)
	{
		while (tmp->prev && (tmp->prev->std >= 2 && tmp->prev->std <= 5))
		{
			data = ft_check_in(tmp, data);
			tmp = tmp->prev;
		}
		if (tmp->std != 0)
			cmd = tmp;
		tmp = ft_util_inout(data, tmp, redir);
		if (!tmp->prev)
			break ;
		tmp = tmp->prev;
	}
	return (tmp);
}

t_cmd	*ft_in(t_data *data, t_cmd *tmp, t_redir *redir)
{
	tmp->redir = malloc(sizeof(t_redir));
	if (!tmp->redir)
		return (NULL);
	ft_init_redir(tmp->redir);
	tmp->redir->fd_in = data->fd_in;
	tmp->redir->redir_std_in = data->std_in;
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
