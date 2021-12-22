/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/12/22 18:39:13 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*ft_redir(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	t_redir	*redir;

// 	tmp = cmd;
// 	cmd->redir = NULL;
// 	while (cmd && cmd->next != NULL)
// 	{
// 		if (cmd->std > 1 && cmd->std <= 5)
// 		{
// 	//printf("cmd = %s std = %d\n", cmd->cmd, cmd->std);
// 			cmd->redir = ft_create_redir(cmd, redir);
// 	printf("cmdc = %s in = %s out = %s\n", cmd->cmd, cmd->redir->fd_in, cmd->redir->fd_out);
// 		}
// 		cmd = cmd->next;
// 	puts("che");
// 		// if (!cmd->cmd && cmd->next != NULL)
// 		// {
// 		// 	while (!cmd->cmd)
// 		// 		cmd = cmd->next;
// 		// }
// 	}
// 	cmd = tmp;
// 	return (cmd);
// }

t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;
	int		exist;

	tmp = cmd;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->std > 1 && tmp->std <= 5)
			exist = 1;
		tmp = tmp->next;
	}
	printf("exist = %d\n", exist);
	if (exist == 0)
	{	
		cmd->redir = NULL;
		return (cmd);
	}
	else
		cmd->redir = ft_create_redir(tmp, cmd, redir); // ou tmp->redir (en mettant la liste redir a la fin donc)
	printf("cmd = %s fdin = %s fdout = %s\n", cmd->cmd, cmd->redir->fd_in, cmd->redir->fd_out);
	return (cmd);
}

t_redir	*ft_create_redir(t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;

	redir = NULL;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	while (tmp && tmp->previous != NULL)
	{
		if (tmp->previous->std == 4 || tmp->previous->std == 5)
		{
			new->fd_in = tmp->cmd;
			tmp->cmd = NULL;
			break;
		}
		tmp = tmp->previous;
	}
	cmd = cmd->next;
	while (cmd/* && cmd->next != NULL*/)
	{
		if (cmd->previous->std == 2 || cmd->previous->std == 3)
		{
			new->fd_out = cmd->cmd;
			cmd->cmd = NULL;
	printf("newfdin = %s newout = %s p %p\n", new->fd_in, new->fd_out, new);
			new->next = NULL;
// pb : ne marche que pour une redir
// il faudrait remalloc new pour creer les maillons suivants s'il y a plsrs >
// comment faire?
		}
		cmd = cmd->next;
	}
	return (new);
}

/*
t_redir	*ft_create_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;
	t_cmd	*tmp_cmd;
	
	redir = NULL;
	tmp = redir;
	tmp_cmd = cmd;
	while (redir != NULL && (redir)->next != NULL)
	{
		puts("che3");
		redir = (redir)->next;
	}
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->fd_out = NULL;
	tmp_cmd = tmp_cmd->next;
	//printf("tcmd = %s\n", tmp_cmd->cmd);
	//while (tmp_cmd && tmp_cmd->next != NULL)
	while (tmp_cmd && tmp_cmd->previous->std > 1 && tmp_cmd->previous->std <= 5)
	{
	printf("cmdin = %s in = %s std = %d\n", tmp_cmd->cmd, new->fd_in, tmp_cmd->previous->std);
		if (tmp_cmd->previous->std == 4 || tmp_cmd->previous->std == 5)
		{
			
			new->fd_in = tmp_cmd->cmd;
			tmp_cmd->cmd = NULL;
		}
		tmp_cmd = tmp_cmd->next;
	}
	if (tmp == NULL)
	{
		puts("che1");
		tmp = new;
	}
	else
		(redir)->next = new;
	return (tmp);
}

t_redir	*ft_create_redir(t_cmd *cmd, t_redir **redir)
{
	int	i;

	i = 0;
	*redir = NULL;
	while (cmd->std > 1 && cmd->std <= 5)
	{	
		if (cmd->std == 2 || cmd->std == 3)
			*redir = ft_left(cmd, *redir, i);
		else if (cmd->std == 4 || cmd->std == 5)
		{
			*redir = ft_right(cmd, *redir, i);
			i++;
		}
		cmd = cmd->next;
	}
	return (*redir);
}
*/
t_redir	*ft_right(t_cmd *cmd, t_redir *redir, int i)
{
	t_redir	*new;
	t_redir	*tmp;
	t_cmd	*tmp_cmd;

	tmp = redir;
	tmp_cmd = cmd;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new = ft_newredir(new, cmd->std);
	new->fd_out = NULL;
	new->next = NULL;
	if (tmp == NULL)
	{
		tmp = new;
	}
	else
	{
		
		redir->next = new;
	}
	printf("cmdin = %s in = %s out = %s\n", cmd->cmd, new->fd_in, new->fd_out);
	return (tmp);
}

t_redir	*ft_left(t_cmd *cmd, t_redir *redir, int i)
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
	//printf("cmdout = %s in = %s out = %s\n", cmd->cmd, new->fd_in, new->fd_out);
	return (tmp);
}

t_redir	*ft_newredir(t_redir *new, int i)
{
	if (i == 2)
	{
		new->std_redir = 2;
		//new->cmd_redir = ">";
	}
	else if (i == 3)
	{
		new->std_redir = 3;
		//new->cmd_redir = ">>";
	}
	else if (i == 4)
	{
		new->std_redir = 4;
		//new->cmd_redir = "<";
	}
	else if (i == 5)
	{
		new->std_redir = 5;
		//new->cmd_redir = "<<";
	}
	return (new);
}
