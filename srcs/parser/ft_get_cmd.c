/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2021/12/25 17:31:49 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd)
{
	int		i;
	char	**cpy;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (i < arg->count)
	{
		if ((ft_check_redir(arg, i) == 1 && (i + 1 < arg->count))
			|| (ft_check_redir(arg, i) == 2 && (i + 1 < arg->count)))
			i ++;
		cpy = ft_strsplit_s(arg->cmds[i], ' ');
		if (cpy[i] == NULL && i < arg->count)
		{
			cpy[i] = ft_strdup(arg->cmds[i]);
			if (!cpy[i])
				return (NULL);
		}
		arg->i_cpy = i++;
		*cmd = ft_parse_cmd(arg, cpy, *cmd);
		if (!*cmd)
			return (NULL);
		
	}
	return (*cmd);
}

t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd)
{
	if (ft_strcmp(cpy[0], "echo") == 0)
		return (ft_parse_echo(arg, cpy, cmd));
	else if (ft_strcmp(cpy[0], "cd") == 0 || ft_strcmp(cpy[0], "pwd") == 0
		|| ft_strcmp(cpy[0], "export") == 0
		|| ft_strcmp(cpy[0], "unset") == 0
		|| ft_strcmp(cpy[0], "env") == 0 || ft_strcmp(cpy[0], "exit") == 0)
		return (ft_parse_builtins(arg, cpy, cmd));
	else if (ft_strcmp(cpy[0], "|") && ft_strcmp(cpy[0], ">")
		&& ft_strcmp(cpy[0], ">>") && ft_strcmp(cpy[0], "<")
		&& ft_strcmp(cpy[0], "<<"))
		return (ft_parse_other(arg, cpy, cmd));
	return (NULL);
}

int	ft_check_redir(t_arg *arg, int i)
{
	if (ft_strcmp(arg->cmds[i], "|") == 0
		|| ft_strcmp(arg->cmds[i], ">") == 0
		|| ft_strcmp(arg->cmds[i], "<") == 0)
		{
		//	puts("che1");
		return (1);
		}
	else if (ft_strcmp(arg->cmds[i], ">>") == 0
		|| ft_strcmp(arg->cmds[i], "<<") == 0)
		{
		//puts("che");
		return (2);
		}
	return (0);
}
