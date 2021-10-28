/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/28 14:28:23 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;
	t_cmd	*tmp;
	t_cmd	*new;
	
	j = 0;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = i;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	if (i == arg->count - 1)
		new->std = 0;
	else if (i < arg->count)
		new->std = ft_std(arg, cmd, i + 1);
	if (!cpy[j])
	{
		new->msg = NULL;
		//printf("builtins1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		//return (ft_print("\n", 0));
	}
	new->spec = NULL;
	new->msg = ft_cpy_msg(arg, cpy, i, j, new);
	printf("builtins2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

t_cmd	*ft_parse_other(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = i;
	new->cmd = ft_strdup(cpy[j]);
	printf("cmd = %s\n", new->cmd);
	j++;
	if (i == arg->count - 1)
		new->std = 0;
	else if (i < arg->count)
		new->std = ft_std(arg, cmd, i + 1);
	if (!cpy[j])
	{
		new->msg = NULL;
		// printf("other1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
		// return (ft_print("\n", 0));
	}
	else
		new->msg = ft_cpy_msg(arg, cpy, i, j, new);
	new->spec = NULL;
	printf("other2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

t_cmd	*ft_parse_special(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int		j;
	t_redir	redir;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nb = i;
	if (i == arg->count - 1)
		new->std = 0;
	else if (i < arg->count)
		new->std = ft_std(arg, cmd, i + 1);
	new->spec = NULL;
	new->msg = NULL;
	new->cmd = ft_strdup(cpy[j]);
	printf("special : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	// if (ft_strncmp(cmd->cmd, ">", ft_strlen(cmd->cmd)) == 0
	// 	|| ft_strncmp(cmd->cmd, ">>", ft_strlen(cmd->cmd)) == 0
	// 	|| ft_strncmp(cmd->cmd, "<", ft_strlen(cmd->cmd)) == 0
	// 	|| ft_strncmp(cmd->cmd, "<<", ft_strlen(cmd->cmd)) == 0)
	// 	redir = ft_redir(arg, cpy, i, cmd, &redir);
	// else
	printf("%p\n", &cmd);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

int	ft_std(t_arg *arg, t_cmd *cmd, int i)
{
	if (ft_strncmp(arg->cmds[i], "|", ft_strlen(arg->cmds[i])) == 0)
		return (1);
		//cmd->std = 1;
	else if (ft_strncmp(arg->cmds[i], ">", ft_strlen(arg->cmds[i])) == 0)
		//cmd->std = 2;
		return (2);
	else if (ft_strncmp(arg->cmds[i], ">>", ft_strlen(arg->cmds[i])) == 0)
		//cmd->std = 3;
		return (3);
	else if (ft_strncmp(arg->cmds[i], "<", ft_strlen(arg->cmds[i])) == 0)
		//cmd->std = 4;
		return (4);
	else if (ft_strncmp(arg->cmds[i], "<<", ft_strlen(arg->cmds[i])) == 0)
		//cmd->std = 5;
		return (5);
	return (0);
}
