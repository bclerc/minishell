/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/12/21 17:26:48 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void trans_redir(t_redir *src, t_redir *dst)
{
	t_redir *tmp;

	if (dst)
	{
		tmp = dst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = src;	
	}
	else
		dst = src;
}

t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	//t_cmd	*past;
	t_redir	*redir;

	tmp = cmd;
	//past = cmd;
	cmd->redir = NULL;
	while (cmd && cmd->next != NULL)
	{
		if (cmd->std > 1 && cmd->std <= 5)
		{
			cmd->redir = ft_create_redir(cmd, &redir);
	//printf("cmd = %s in = %s out = %s\n", cmd->cmd, cmd->redir->fd_in, cmd->redir->fd_out);
			//trans_redir(cmd->redir, past->redir);
			//past->next = cmd->next;
		}
		//past = cmd;
		cmd = cmd->next;
		printf("sdad\n");
	}
	cmd = tmp;
	return (cmd);
}

t_redir	*ft_create_redir(t_cmd *cmd, t_redir **redir)
{
	*redir = NULL;
	while (cmd->std > 1 && cmd->std <= 5)
	{if (cmd->std == 2 || cmd->std == 3)
		*redir = ft_left(cmd, *redir);
	else if (cmd->std == 4 || cmd->std == 5)
		*redir = ft_right(cmd, *redir);
	cmd = cmd->next;}
	return (*redir);
}

t_redir	*ft_right(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(new, cmd->std);
	new->fd_in = cmd->next->cmd;
	new->fd_out = NULL;
	cmd->next->cmd = NULL;
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	printf("cmd = %s in = %s out = %s\n", cmd->cmd, new->fd_in, new->fd_out);
	return (tmp);
}

t_redir	*ft_left(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(new, cmd->std);
	new->fd_out = cmd->next->cmd;
	new->fd_in = NULL;
	cmd->next->cmd = NULL;
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	printf("cmd = %s in = %s out = %s\n", cmd->cmd, new->fd_in, new->fd_out);
	return (tmp);
}

t_redir	*ft_newredir(t_redir *new, int i)
{
	if (i == 2)
	{
		new->std_redir = 2;
		new->cmd_redir = ">";
	}
	else if (i == 3)
	{
		new->std_redir = 3;
		new->cmd_redir = ">>";
	}
	else if (i == 4)
	{
		new->std_redir = 4;
		new->cmd_redir = "<";
	}
	else if (i == 5)
	{
		new->std_redir = 5;
		new->cmd_redir = "<<";
	}
	return (new);
}
