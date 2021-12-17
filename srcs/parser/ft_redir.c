/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/12/16 10:08:19 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir *redir;

	tmp = cmd;
	while (cmd && cmd->next != NULL)
	{
		printf("cmd= %s std = %d\n", cmd->cmd, cmd->std);
		// if (ft_strcmp(cmd->cmd, "<") == 0 || ft_strcmp(cmd->cmd, "<<") == 0
		// 		|| ft_strcmp(cmd->cmd, ">") == 0 || ft_strcmp(cmd->cmd, ">>") == 0)
		if (cmd->std > 1 && cmd->std <= 5)
		{
		//printf("std = %d\n", cmd->std);
			cmd->redir = ft_create_redir(cmd, &redir);
			//printf("cmd->redirin = %s cmd->redirout = %s cmd->redirstd = %d\n", cmd->redir->fd_in_redir, cmd->redir->fd_out_redir, cmd->redir->std_redir);
			break;
		}
		cmd = cmd->next;
	}
	cmd = tmp;
	return (cmd);
}

t_redir	*ft_create_redir(t_cmd *cmd, t_redir **redir)
{
	*redir = NULL;
	//while (cmd && cmd->next != NULL)
	{
		if (cmd->std == 2 || cmd->std == 3)
			*redir = ft_right(cmd, *redir);
		else if (cmd->std == 4 || cmd->std == 5)
			*redir = ft_left(cmd, *redir);
		// else if (cmd->std == 1)
		// 	*redir = ft_pipe(cmd, *redir);
		cmd = cmd->next->next;
	}
	return (*redir);
}

t_redir	*ft_right(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	printf("msg1 = %s\n", cmd->next->msg);
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(cmd, new, cmd->std);
	//if (cmd->next->next->msg && ft_strcmp(cmd->cmd, "echo") == 0) // ecrire dans le fichier le msg complet (avant et apres le >)
		//new->fd_in_redir = ft_strjoin(cmd->msg, cmd->next->msg);
	if (cmd->msg && ft_strcmp(cmd->cmd, "echo") == 0)
		new->msg = ft_strdup(cmd->msg);
	//else
	new->fd_in_redir = cmd->next->cmd;
	//new->fd_out_redir = cmd->next->cmd; // mais souci si 2 noms apres un > : il peut y avoir plsrs noms de fichiers out
	printf("in = %s s = %d\n", new->fd_in_redir, new->std_redir);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}
/*
t_redir	*ft_pipe(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(cmd, new, cmd->std);
	if (cmd->next->next->msg && ft_strcmp(cmd->cmd, "echo") == 0) // ecrire dans le fichier le msg complet (avant et apres le >)
		new->fd_in = ft_strjoin(cmd->msg, cmd->next->next->msg);
	else
		new->fd_in = cmd->msg;
	new->fd_out = cmd->next->next->cmd; // mais souci si 2 noms apres un > : il peut y avoir plsrs noms de fichiers out
	printf("out = %s s = %d\n", new->fd_out, new->std_redir);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}
*/
t_redir	*ft_left(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	printf("msg2 = %s\n", cmd->msg);
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(cmd, new, cmd->std);
	// if (cmd->next->next->msg && ft_strcmp(cmd->cmd, "echo") == 0) // ecrire dans le fichier le msg complet (avant et apres le >)
	// 	new->fd_in_redir = ft_strjoin(cmd->msg, cmd->next->next->msg);
	// else
	// 	new->fd_in_redir = cmd->msg;
	// new->fd_out_redir = cmd->next->next->cmd; // mais souci si 2 noms apres un > : il peut y avoir plsrs noms de fichiers out
	if (cmd->msg && ft_strcmp(cmd->cmd, "echo") == 0)
		new->msg = ft_strdup(cmd->msg);
	new->fd_out_redir = cmd->next->cmd;
	printf("out = %s s = %d\n", new->fd_out_redir, new->std_redir);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}

t_redir	*ft_newredir(t_cmd *cmd, t_redir *new, int i)
{
	(void)cmd;
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
	else if (i == 1)
	{
		new->std_redir = 1;
		new->cmd_redir = "|";
	}
	printf("i = %d s = %d c = %s\n", i, new->std_redir, new->cmd_redir);
	return (new);
}
