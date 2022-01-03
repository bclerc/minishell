/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2022/01/03 18:59:32 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_redir(t_cmd *cmd)
{
	t_cmd   *tmp;
	char	*in;
	t_redir *redir;
	int     exist;
	int		std_in;

	tmp = cmd;
	redir = NULL;
	cmd->redir = NULL;
	exist = ft_exist(tmp);
	//printf("ex = %d tmp->cmd %s cmd = %s\n", exist, tmp->cmd, cmd->cmd);
	if (exist == 0)
		return (cmd);
	else
	{   
		if (exist == 1)
		{
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			cmd = ft_fillin(tmp, redir);
			//printf("redir1 %p\n", cmd->redir);
			//printf("redir1 cmd in %s std %d msg %s\n", cmd->redir->fd_in, cmd->redir->redir_std_in, cmd->redir->redir_msg);
		}
		else if (exist == 2)
		{
			tmp = ft_fillout(cmd, redir);
			tmp = cmd;
			return (tmp);
			//printf("redir2 cmd %s out %s std %d msg %s\n", tmp->cmd, tmp->redir->fd_out, tmp->redir->redir_std_out, tmp->redir->redir_msg);
			
		}
		else if (exist == 3)
		{
			// in = ft_search_in(tmp);
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			while (tmp && tmp->previous != NULL)
			{
				if (tmp->previous->std == 4 || tmp->previous->std == 5)
				{
					// in = malloc(sizeof(char) * (ft_strlen(tmp->cmd) + 1));
					// if (!in)
					// 	return (NULL);
					in = tmp->cmd;
					std_in = tmp->previous->std;
					tmp->cmd = NULL;
					break ;
				}
				if (!tmp->previous)
					break ;
				tmp = tmp->previous;
            //printf("redir : p %p in %s std %d msg = %s\n", redir, redir->fd_in, redir->redir_std_in, redir->redir_msg);;      
			}
			 printf(" cmd = %s\n", tmp->cmd);
			tmp = cmd;
			tmp = ft_fillinout(cmd, redir, in, std_in);
			//puts("che");
			tmp = cmd;
			//printf("redir3 %p cmd %s in %s out %s\n", tmp->redir, tmp->cmd, tmp->redir->fd_in, tmp->redir->fd_out);
			return (tmp);
		}
	}
	return (cmd);
}

t_cmd	*ft_fillin(t_cmd *cmd, t_redir *redir)
{
	char	*fd_in;
	char	*msg;
	int		std_in;
	
	fd_in = NULL;
	msg = NULL;
	std_in = 0;
	while (cmd->previous->std != 4 && cmd->previous->std != 5)
	{	
		if (!cmd->previous)
			break ;
		cmd = cmd->previous;
	}
	while (cmd->previous != NULL && (cmd->previous->std == 4 || cmd->previous->std == 5))
	{
		if (!fd_in)
		{
			fd_in = cmd->cmd;
			std_in = cmd->previous->std;
			cmd->cmd = NULL;
		}
		else if (fd_in)
			cmd->cmd = NULL;
		if (!cmd->previous)
			break ;
		cmd = cmd->previous;
	}
	cmd->redir = malloc(sizeof(t_redir));
	if (!cmd->redir)
		return (NULL);
	ft_init_redir(cmd->redir);
	cmd->redir->fd_in = fd_in;
	cmd->redir->redir_std_in = std_in;
	if (cmd->msg)
		cmd->redir->redir_msg = cmd->msg;
    //printf("cmd %s redir : in %s std %d msg = %s\n", cmd->cmd, cmd->redir->fd_in, cmd->redir->redir_std_in, cmd->redir->redir_msg);
	while (cmd && cmd->previous != NULL)
	{
		if ((cmd->previous->std == 4 || cmd->previous->std == 5))
			cmd->cmd = NULL;
		
		if (!cmd->previous)
			break ;
		cmd = cmd->previous;
	}
	//printf("cmd2 %s\n", cmd->cmd);
	return (cmd);
}

t_cmd	*ft_fillout(t_cmd *tmp, t_redir *redir)
{
	t_cmd	*cmd;

	while (tmp && tmp->next != NULL)
	{
		if (tmp->std == 2 || tmp->std == 3)
		{
			cmd = tmp;
			tmp = tmp->next;
			while (tmp->previous->std == 2 || tmp->previous->std == 3)
			{
				cmd->redir = ft_create_out(tmp, redir);
				if (!tmp->next)
					break ;
				if (tmp->std != 2 && tmp->std != 3)
					break ;
				tmp = tmp->next;
			}
			tmp = cmd;
			//printf("redir out %s cmd %s\n", tmp->redir->fd_out, tmp->cmd);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_redir	*ft_create_out(t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	ft_init_redir(new);
	new->redir_std_out = cmd->previous->std;
	cmd->previous->std = 0;
	new->fd_out = cmd->cmd;
	cmd->cmd = NULL;
	if (cmd->previous->msg)
	{
		new->redir_msg = cmd->previous->msg;
		if (cmd->std == 2 || cmd->std == 3)
			cmd->msg = cmd->previous->msg;
	}
	new->next = NULL;
	//printf("new : cmd %s out %s std %d msg %s\n", cmd->previous->cmd, new->fd_out, new->redir_std_out, new->redir_msg);
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}

t_redir	*ft_create_out2(char *in, int std_in, t_cmd *cmd, t_redir *redir)
{
	t_redir	*new;
	t_redir	*tmp;

	tmp = redir;
	while (redir && redir->next != NULL)
		redir = redir->next;
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	ft_init_redir(new);
		printf("cmd = %s msg = %s std %d\n", cmd->cmd, cmd->previous->msg, cmd->previous->std);
	new->redir_std_out = cmd->previous->std;
	new->fd_out = cmd->cmd;
	new->fd_in = in;
	new->redir_std_in = std_in;

	cmd->cmd = NULL;
	if (cmd->previous->msg)
	{
		new->redir_msg = cmd->previous->msg;
//		if (cmd->previous->std >= 2 && cmd->previous->std <= 5)
//			cmd->msg = cmd->previous->msg;
		//cmd->previous->msg = NULL;
	}
	new->next = NULL;
	printf("new : out %s in %s stdout %d stdin %d msg %s\n", new->fd_out, new->fd_in, new->redir_std_out, new->redir_std_in, new->redir_msg);
	if (tmp == NULL)
		tmp = new;
	else
		redir->next = new;
	return (tmp);
}

t_cmd	*ft_fillinout(t_cmd *tmp, t_redir *redir, char *in, int std_in)
{
	t_cmd	*cmd;

	cmd = tmp;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->std == 2 || tmp->std == 3)
		{
			tmp = tmp->next;
			while (tmp->previous->std == 2 || tmp->previous->std == 3)
			{
	//printf("cmd %s std %d\n", tmp->cmd, tmp->std);
				tmp->redir = ft_create_out2(in, std_in, tmp, redir);
				if (!tmp->next)
					break;
				tmp = tmp->next;
			}
		}
		//printf("std %d cmd %s\n", tmp->std, tmp->cmd);
		if (tmp->std != 2 && tmp->std != 3)
			tmp = tmp->next;
	}
	return (tmp);
}

// {
// 	cmd = cmd->next;
// 	while (cmd->previous->std != 2 || cmd->previous->std != 3)
// 	{
// 		if (cmd->previous->std == 2 || cmd->previous->std == 3)
// 			break ;
// 		cmd = cmd->next;
// 	}
// 	//printf("cmd %s\n", cmd->cmd);
// 	redir->fd_out = cmd->cmd;
//     printf("redir std %d in %s out %s\n", cmd->previous->std, redir->fd_in, redir->fd_out);
// 	cmd->cmd = NULL;
// 	redir->redir_std_out = cmd->previous->std;
// 	// if (cmd->next != NULL)
// 	if (cmd && cmd->next != NULL)
// 	{
// 		cmd = cmd->next;
// 		cmd = ft_fillout(cmd, redir); // ou cmd->redir?
// 	}
// 	printf("cmd %s\n", cmd->cmd);
// 			while (cmd && cmd->next != NULL)
// 			{
// 			puts("che");
// 				if (cmd->redir)
// 					printf("cmd %s out %s msg %s\n", cmd->cmd, cmd->redir->fd_out, cmd->msg);
// 				cmd = cmd->next;
// 			}
// 	return (cmd);
// }

// t_redir	*ft_create_pipe(t_cmd *cmd, t_redir *redir)
// {
// 	t_redir	*new;
// 	t_redir	*tmp;

// 	tmp = redir;
// 	while (redir && redir->next != NULL)
// 		redir = redir->next;
// 	new = malloc(sizeof(t_redir));
// 	if (!new)
// 		return (0);
// 	ft_init_redir(new);
// 	printf("std %d\n", cmd->std);
// 	new->redir_std_pipe = cmd->std;
// //		puts("coucou");
// 	new->fd_in = NULL;
// 	if (cmd->next->msg)
// 	{
// 		new->redir_msg = cmd->next->msg;
// 		cmd->next->msg = NULL;
// 	}
// 	new->next = NULL;
// 	printf("new : std %d msg %s\n", new->redir_std_pipe, new->redir_msg);
// 	if (tmp == NULL)
// 		tmp = new;
// 	else
// 		redir->next = new;
// 	return (tmp);
// }
