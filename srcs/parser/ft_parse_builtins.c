/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:26:09 by astrid            #+#    #+#             */
/*   Updated: 2021/12/18 15:56:40 by asgaulti         ###   ########.fr       */
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
		new->std = ft_std(arg, arg->i_cpy + 1);
	if (new->std >= 2 && new->std <= 5)
		ft_fill_fd(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
		new->msg = ft_cpy_msg(arg, cpy, j, new);
	new->spec = NULL;
	printf("builtins2 : cmd = %s, msg = %s in = %s out = %s\n", new->cmd, new->msg, new->fd_in, new->fd_out);
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
	j++;
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, arg->i_cpy + 1);
	if (new->std >= 2 && new->std <= 5)
		ft_fill_fd(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
		new->msg = ft_cpy_msg(arg, cpy, j, new);
	new->spec = NULL;
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	printf("other2 : cmd = %s, msg = %s in = %s out = %s\n", new->cmd, new->msg, new->fd_in, new->fd_out);
	return (tmp);
}

t_cmd	*ft_parse_special(t_arg *arg, char **cpy, t_cmd *cmd)
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
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, arg->i_cpy);
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

void	ft_fill_fd(t_arg *arg, t_cmd *new)
{
	int		i;
	int		j;
	char	*tmp;

	i = arg->i_cpy;
	j = 0;
	if (new->std == 2 || new->std == 3)
		ft_spec_out(new, arg);
	else if (new->std == 4 || new->std == 5)
		ft_spec_in(new, arg);
}
