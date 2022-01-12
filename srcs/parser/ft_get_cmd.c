/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2022/01/12 17:19:08 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_utils_cmd.c for aux fcts
t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd)
{
	char	**cpy;

	arg->i = 0;
	while (arg->i < arg->count)
	{
		arg->i = ft_cmd_i(arg, arg->i);
		cpy = ft_strsplit(arg->cmds[arg->i], ' ');
		if (!cpy)
			return (NULL);
		if (cpy[0] && (cpy[0][0] == '\'' || cpy[0][0] == '"'))
			cpy[0] = ft_cpy0(cpy[0], arg);
		if (cpy[0] == NULL && arg->i < arg->count)
		{
			cpy[0] = ft_strdup(arg->cmds[arg->i]);
			if (!cpy[0])
				return (NULL);
		}
		arg->i_cpy = arg->i++;
		*cmd = ft_parse_cmd(arg, cpy, *cmd);
		if (!*cmd)
			return (NULL);
		if (cpy)
			rm_split(cpy);
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
		return (1);
	else if (ft_strcmp(arg->cmds[i], ">>") == 0
		|| ft_strcmp(arg->cmds[i], "<<") == 0)
		return (2);
	return (0);
}
