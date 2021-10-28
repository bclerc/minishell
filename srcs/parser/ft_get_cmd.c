/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2021/10/28 12:39:48 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd)
{
	int		i;
	char	**cpy;

	i = 0;
	while (i < arg->count)
	{
		//printf("arg[%d] = %s\n", i, arg->cmds[i]);
		cpy = ft_strsplit_s(arg->cmds[i], ' ');
		if (cpy[i] == NULL && i < arg->count)
			cpy[i] = ft_strdup(arg->cmds[i]);
		*cmd = ft_parse_cmd(arg, cpy, i, *cmd);
			puts("che1");
		if (!*cmd)
		{
			return (NULL);
		}
		i++;
	}
	//if (ft_strncmp(arg->cmds[i], "echo", ft_strlen(arg->cmds[i])) == 0)
	//	return (ft_parse_echo(arg, &cmd, i));
	// printf("i1 = %d\n", i);
	//if (i == -1)
	//	return (-1);
	//i++;
	// printf("i2 = %d\n", i);
	// if (!arg->cmds[i])
	// 	return (-1); 
	// ou plutot lancer l'exec??
	//return (i);
	return (*cmd);
}

t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	printf("cpy[0] = %s\n", cpy[0]);
	if (ft_strncmp(cpy[0], "echo", ft_strlen(cpy[0])) == 0)
		return (ft_parse_echo(arg, cpy, i, cmd));
	else if (ft_strncmp(cpy[0], "cd", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "pwd", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "export", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "unset", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "env", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "exit", ft_strlen(cpy[0])) == 0)
		return (ft_parse_builtins(arg, cpy, i, cmd));
	else if (ft_strncmp(cpy[0], "|", ft_strlen(cpy[0])) 
			&& ft_strncmp(cpy[0], ">", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], ">>", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], "<", ft_strlen(cpy[0]))
			&& ft_strncmp(cpy[0], "<<", ft_strlen(cpy[0])))
		return (ft_parse_other(arg, cpy, i, cmd));		
	return (ft_parse_special(arg, cpy, i, cmd));
}
