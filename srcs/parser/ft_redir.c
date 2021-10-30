/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/10/30 12:15:07 by astrid           ###   ########.fr       */
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
t_cmd	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd)
{
	cmd->fd = cmd->cmd;
	cmd->cmd = NULL;
	//cmd->path = ??
	return (cmd);
}