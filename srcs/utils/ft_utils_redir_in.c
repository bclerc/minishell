/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:55:48 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 14:04:57 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_fillin(t_cmd *cmd, t_redir *redir)
{
	char	*fd_in;
	int		std_in;

	fd_in = NULL;
	std_in = 0;
	cmd = ft_util_in1(cmd);
	while (cmd->prev != NULL && (cmd->prev->std == 4
			|| cmd->prev->std == 5))
	{
		if (!fd_in)
		{
			fd_in = cmd->cmd;
			std_in = cmd->prev->std;
			cmd->cmd = NULL;
		}
		else if (fd_in)
			cmd->cmd = NULL;
		if (!cmd->prev)
			break ;
		cmd = cmd->prev;
	}
	cmd = ft_util_in2(cmd->redir, cmd, fd_in, std_in);
	return (cmd);
}

t_cmd	*ft_util_in1(t_cmd *cmd)
{
	while (cmd->prev->std != 4 && cmd->prev->std != 5)
	{	
		if (!cmd->prev)
			break ;
		cmd = cmd->prev;
	}
	return (cmd);
}

t_cmd	*ft_util_in2(t_redir *redir, t_cmd *cmd, char *fd_in, int std_in)
{
	cmd->redir = malloc(sizeof(t_redir));
	if (!cmd->redir)
		return (NULL);
	ft_init_redir(cmd->redir);
	cmd->redir->fd_in = fd_in;
	cmd->redir->redir_std_in = std_in;
	if (cmd->msg)
		cmd->redir->redir_msg = cmd->msg;
	while (cmd && cmd->prev != NULL)
	{
		if ((cmd->prev->std == 4 || cmd->prev->std == 5))
			cmd->cmd = NULL;
		if (!cmd->prev)
			break ;
		cmd = cmd->prev;
	}
	return (cmd);
}
