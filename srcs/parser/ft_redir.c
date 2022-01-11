/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2022/01/11 12:13:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;
	int		exist;

	tmp = cmd;
	redir = NULL;
	cmd->redir = NULL;
	exist = ft_exist(tmp);
	if (exist == 0)
		return (cmd);
	else
		cmd = ft_isredir(exist, tmp, cmd, redir);
	return (cmd);
}

int	ft_exist(t_cmd *tmp)
{
	int	exist;

	exist = 0;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->std == 4 || tmp->std == 5)
		{
			if (!exist)
				exist = 1;
			else if (exist == 2)
				exist = 3;
		}
		else if (tmp->std == 2 || tmp->std == 3)
		{
			if (!exist)
				exist = 2;
			else if (exist == 1)
				exist = 3;
		}
		tmp = tmp->next;
	}
	return (exist);
}

t_cmd	*ft_isredir(int exist, t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	if (exist == 1)
	{
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		cmd = ft_fillin(tmp, redir);
		if (!cmd)
			return (NULL);
	}
	else if (exist == 2)
	{
		tmp = ft_fillout(cmd, redir);
		if (!tmp)
			return (NULL);
		tmp = cmd;
		return (tmp);
	}
	else if (exist == 3)
	{
		tmp = ft_inout(tmp, cmd, redir);
		if (!tmp)
			return (NULL);
		tmp = cmd;
		return (tmp);
	}
	return (cmd);
}
