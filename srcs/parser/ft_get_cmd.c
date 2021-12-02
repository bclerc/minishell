/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2021/12/02 14:01:09 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_cmd(t_arg *arg, t_cmd *cmd)
{
	int		i;
	char	**cpy;

	i = 0;
	while (i < arg->count)
	{
		cpy = ft_strsplit_s(arg->cmds[i], ' ');
		if (ft_parse_cmd(arg, cpy, i, cmd) == -1)
		{
			puts("che");
			return (-1);
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

	return (i);
}

int	ft_parse_cmd(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	if (ft_strncmp(cpy[0], "echo", ft_strlen(cpy[0])) == 0)
		return (ft_parse_echo(arg, cpy, i, cmd));
	else if (ft_strncmp(cpy[0], "cd", ft_strlen(cpy[0])) == 0)
		return (ft_parse_cd(arg, cpy, i, cmd));
	else if (ft_strncmp(cpy[0], "pwd", ft_strlen(cpy[0])) == 0
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
	return (0);
}
