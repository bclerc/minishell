/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2022/01/09 19:29:43 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*new;

	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	new->redir = NULL;
	if (!new)
		return (NULL);
	new = ft_fill_builtin(cpy, new, arg);
	if (!new)
		return (NULL);
	if (tmp == NULL)
	{
		new->previous = NULL;
		tmp = new;
	}
	else
		cmd = ft_cmd_builtin(cmd, tmp, new);
	//printf("new2 = %s sp %s msg = %s std = %d\n", new->cmd, new->spec, new->msg, new->std);
	return (tmp);
}

t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*new;

	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	new->redir = NULL;
	if (!new)
		return (NULL);
	new = ft_fill_other(cpy, new, arg);
	if (tmp == NULL)
	{
		new->previous = NULL;
		tmp = new;
	}
	else
		cmd = ft_cmd_builtin(cmd, tmp, new);
	//printf("new3 = %s sp %s msg = %s std = %d\n", new->cmd, new->spec, new->msg, new->std);
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
