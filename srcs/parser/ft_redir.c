/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/12/23 14:17:33 by asgaulti         ###   ########.fr       */
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
	//printf("exist = %d\n", exist);
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
/*
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
				puts("che");
			if (!new->fd_in)
			{
				new->fd_in = tmp->cmd;
				tmp->cmd = NULL;	
			}
			if (new->fd_in && new->fd_out)
				break;
		}
		else if (tmp->previous->std == 2 || tmp->previous->std == 3)
		{
			if (!new->fd_out)
			{
				new->fd_out = tmp->cmd;
				tmp->cmd = NULL;
			}
			//break;
		}
	//printf("newfdin = %s newout = %s p %p\n", new->fd_in, new->fd_out, new);
		tmp = tmp->previous;
	}
// 	cmd = cmd->next;
// 	while (cmd && cmd->next != NULL)
// 	{
// 		if (cmd->previous->std == 2 || cmd->previous->std == 3)
// 		{
// 			new->fd_out = cmd->cmd;
// 			cmd->cmd = NULL;
// 			new->next = NULL;
// // pb : ne marche que pour une redir
// // il faudrait remalloc new pour creer les maillons suivants s'il y a plsrs >
// // comment faire?
// 		}
// 		cmd = cmd->next;
// 	}
	return (new);
}
*/

t_redir	*ft_create_redir(t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp_re;

	//redir = NULL;
	tmp_re = redir;
	while (redir != NULL && redir->next != NULL)
		redir = redir->next;
	while (cmd->std > 1 && cmd->std <= 5)
	{	
		new = malloc(sizeof(t_redir));
		if (!new)
			return (0);		
		/*if (cmd->std == 2 || cmd->std == 3)
			redir = ft_left(cmd, redir);
		else if ((cmd->std == 4 || cmd->std == 5) && !new->fd_in)
		*/	new = ft_right(tmp, redir);
		printf("fdin = %s\n", new->fd_in);
		cmd = cmd->next;
	}
	//printf("cmdin = %s in = %s out = %s\n", cmd->cmd, new->fd_in, new->fd_out);
	if (tmp_re == NULL)
		tmp_re = new;
	else
		redir->next = new;
	return (new);
}

t_redir	*ft_right(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	// tmp = redir;
	// tmp_cmd = cmd;
	// while (redir != NULL && redir->next != NULL)
	// 	redir = redir->next;
	// new = malloc(sizeof(t_redir));
	// if (!new)
	// 	return (0);
	// new = ft_newredir(new, cmd->std);
	new->fd_out = NULL;
	new->next = NULL;
	while (cmd && cmd->previous != NULL)
	{
		if ((cmd->previous->std == 4 || cmd->previous->std == 5) && !new->fd_in)
		{
			new->fd_in = cmd->cmd;
			cmd->cmd = NULL;
			break;
		}
		cmd = cmd->previous;
	}
	return (new);
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
