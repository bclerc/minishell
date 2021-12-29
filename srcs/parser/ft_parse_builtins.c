/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/12/29 18:11:14 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	t_cmd	*tmp;
	t_cmd	*tmp2;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	tmp2 = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->builtin = 1;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	ft_fill_std(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
		new->msg = ft_cpy_msg(arg, cpy, j, new);
	new->spec = NULL;
	new->next = NULL;
	if (tmp == NULL)
	{
		new->previous = NULL;
		tmp = new;
	}
	else
	{
		cmd->next = new;
		if (tmp2->next != NULL)
		{
			while (tmp2->next->next != NULL)
			{
				tmp2 = tmp2->next;
				
			}		
			new->previous = tmp2;
		}
		// if (new->previous->std > 2 && new->previous->std <= 5)
		// 	new = ft_redir(new);
		cmd = new;
	//printf("new2 = %s next = %p std = %d\n", cmd->cmd, cmd->next, cmd->std);
	}
	return (tmp);
}

t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	t_cmd	*tmp;
	t_cmd	*tmp2;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	tmp2 = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->builtin = 0;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	ft_fill_std(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
		new->msg = ft_cpy_msg(arg, cpy, j, new);
	new->spec = NULL;
	new->next = NULL;
	if (tmp == NULL)
	{
		new->previous = NULL;
		tmp = new;
	}
	else
	{
		cmd->next = new;
		if (tmp2->next != NULL)
		{
			while (tmp2->next->next != NULL)
			{
				tmp2 = tmp2->next;
				
			}		
			new->previous = tmp2;
		}
		// if (new->previous->std > 2 && new->previous->std <= 5)
		// 	new = ft_redir(new);
		cmd = new;
	//printf("new3 = %s msg = %s std = %d\n", cmd->cmd, cmd->msg, cmd->std);
	}
	return (tmp);
}

int	ft_std(t_arg *arg, int i)
{
	if (ft_strncmp(arg->cmds[i], "|", ft_strlen(arg->cmds[i])) == 0)
		return (1);
	else if (ft_strncmp(arg->cmds[i], ">", ft_strlen(arg->cmds[i])) == 0)
		return (2);
	else if (ft_strncmp(arg->cmds[i], ">>", ft_strlen(arg->cmds[i])) == 0)
		return (3);
	else if (ft_strncmp(arg->cmds[i], "<", ft_strlen(arg->cmds[i])) == 0)
		return (4);
	else if (ft_strncmp(arg->cmds[i], "<<", ft_strlen(arg->cmds[i])) == 0)
		return (5);
	return (0);
}

void	ft_fill_std(t_arg *arg, t_cmd *new)
{
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, arg->i_cpy + 1);
}
