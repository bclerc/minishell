/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2021/11/07 17:54:31 by astrid           ###   ########.fr       */
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
		cpy = ft_strsplit_s(arg->cmds[i], ' ');
		if (cpy[i] == NULL && i < arg->count)
			cpy[i] = ft_strdup(arg->cmds[i]);
		arg->i_cpy = i;
		*cmd = ft_parse_cmd(arg, cpy, *cmd);
		if (!*cmd)
		{
			return (NULL);
		}
		i++;
	}
	return (*cmd);
}

t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd)
{
	if (ft_strncmp(cpy[0], "echo", ft_strlen(cpy[0])) == 0)
		return (ft_parse_echo(arg, cpy, cmd));
	else if (ft_strncmp(cpy[0], "cd", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "pwd", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "export", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "unset", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "env", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "exit", ft_strlen(cpy[0])) == 0)
		return (ft_parse_builtins(arg, cpy, cmd));
	else if (ft_strncmp(cpy[0], "|", ft_strlen(cpy[0])) 
			&& ft_strncmp(cpy[0], ">", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], ">>", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], "<", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], "<<", ft_strlen(cpy[0])))
		return (ft_parse_other(arg, cpy, cmd));		
	return (ft_parse_special(arg, cpy, cmd));
}
