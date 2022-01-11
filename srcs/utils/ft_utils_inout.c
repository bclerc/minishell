/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:52:06 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 21:13:13 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_check_in(t_cmd *tmp, t_data *data)
{
	if ((tmp->prev->std == 4 || tmp->prev->std == 5) && !data->fd_in)
	{
		data->fd_in = tmp->cmd;
		tmp->cmd = NULL;
		data->std_in = tmp->prev->std;
		if (tmp->prev->msg)
			data->msg = tmp->prev->msg;
	}
	else if ((tmp->prev->std == 4 || tmp->prev->std == 5) && data->fd_in)
		tmp->cmd = NULL;
	return (data);
}

t_cmd	*ft_within(t_cmd *tmp, t_data *data, t_redir *redir)
{
	t_cmd	*cpy;

	tmp = ft_in(data, tmp, redir);
	if (!tmp)
		return (NULL);
	cpy = tmp;
	while (cpy->next != NULL && (cpy->std >= 2 && cpy->std <= 5))
	{
		if ((cpy->std == 2 || cpy->std == 3) && data->fd_in)
		{
			tmp->redir->fd_out = cpy->next->cmd;
			cpy->next->cmd = NULL;
			tmp->redir->redir_std_out = cpy->std;
			tmp->redir->next = NULL;
			data->fd_in = NULL;
		}
		else if ((cpy->std == 2 || cpy->std == 3) && !data->fd_in)
		{
			if (tmp->redir->redir_msg)
				data->msg = tmp->redir->redir_msg;
			tmp->redir = ft_out(cpy, tmp->redir, data->msg);
		}
		cpy = cpy->next;
	}
	return (tmp);
}

t_cmd	*ft_util_inout(t_data *data, t_cmd *tmp, t_redir *redir)
{
	t_cmd	*cpy;

	if (data->fd_in)
		tmp = ft_within(tmp, data, redir);
	else if (!data->fd_in)
	{
		redir = NULL;
		tmp->redir = NULL;
		cpy = tmp;
		while (cpy->next != NULL && (cpy->std == 2 || cpy->std == 3))
		{
			tmp->redir = ft_out(cpy, tmp->redir, data->msg);
			cpy = cpy->next;
		}
	}
	return (tmp);
}
