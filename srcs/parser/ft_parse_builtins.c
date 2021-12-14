/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/12/14 13:57:50 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = arg->i_cpy;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, cmd, arg->i_cpy + 1);
	if (!cpy[j])
		new->msg = NULL;
	new->spec = NULL;
	new->msg = ft_cpy_msg(arg, cpy, j, new);
	//printf("builtins2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = arg->i_cpy;
	new->cmd = ft_strdup(cpy[j]);
	//printf("cmd = %s cpy[j] = %s\n", new->cmd, cpy[j]);
	j++;
	//printf("cpy[j] = %s\n", cpy[j]);
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, cmd, arg->i_cpy + 1);
	if (!cpy[j])
	{
		new->msg = NULL;
		// printf("other1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		// return (ft_print("\n", 0));
	}
	else
		new->msg = ft_cpy_msg(arg, cpy, j, new);
	new->spec = NULL;
	//printf("other2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

t_cmd	*ft_parse_special(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	//printf("i = %d c = %d\n", arg->i_cpy, arg->count);
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = arg->i_cpy;
	//printf("i_cpy = %d c = %d\n", arg->i_cpy, arg->count);
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, cmd, arg->i_cpy);
	new->spec = NULL;
	new->msg = NULL;
	new->cmd = ft_strdup(cpy[j]);
	new->next = NULL;
	//printf("special : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std);
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}


int	ft_std(t_arg *arg, t_cmd *cmd, int i)
{
	(void)cmd;
	//printf("cmd[%d] = %s\n", arg->i_cpy, arg->cmds[arg->i_cpy]);
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
