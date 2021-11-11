/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/11/11 17:05:04 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_redir	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd, t_redir **redir)
{
	*redir = ft_create_redir(cmd, * redir);
	*redir = cmd;
	printf("redir_std = %d\n", (*redir)->std_redir);
	// stocker la cmd suivant les chevrons (msg et std) 
	// + checker la cmd suiv : si chevron next pointe sur nouveau maillon de redir
	// si pipe next repointe sur cmd
	// si null next pointe sur null
	return (*redir);
}

t_redir	*ft_create_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->std_redir = cmd->std;
	new->fd = -1;
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		stack_a->next = new;
	return (tmp);
}*/
t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir *redir;

	tmp = cmd;
	(void)redir;
	while (cmd && cmd->next != NULL)
	{
		// if (ft_strcmp(cmd->cmd, "<") == 0 || ft_strcmp(cmd->cmd, "<<") == 0
		// 		|| ft_strcmp(cmd->cmd, ">") == 0 || ft_strcmp(cmd->cmd, ">>") == 0)
		if (cmd->std > 1 && cmd->std <= 5)
		{
			cmd->redir = ft_create_redir(cmd, &redir);
			break;
		}
		cmd = cmd->next;
	}
	//printf("cmd->cmd = %s next = %p\n", cmd->cmd, &cmd->next);
	cmd = tmp;
	return (cmd);
}

t_redir	*ft_create_redir(t_cmd *cmd, t_redir **redir)
{
	*redir = NULL;
	while (cmd && cmd->next != NULL)
	{
		if (cmd->std == 2 || cmd->std == 3)
			*redir = ft_right(cmd, *redir);
		cmd = cmd->next->next;
	}
	return (*redir);
}

t_redir	*ft_right(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	printf("msg = %s\n", cmd->msg);
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
	puts ("che");
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}

t_redir	*ft_newredir(t_cmd *cmd, t_redir *new, int i)
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
	printf("i = %d s = %d c = %s\n", i, new->std_redir, new->cmd_redir);
	return (new);
}