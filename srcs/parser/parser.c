/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/19 17:06:48 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *str, char **envp)
{
	t_arg	arg;
	int		i;
	
	i = 0;
	ft_get_arg(str, &arg);
	// while (arg.cmds[i])
	// {
	// 	printf("cmds = %s\n", arg.cmds[i]);
	// 	i++;
	// }
	while (arg.cmds[i])
	{
		if (ft_get_cmd(&arg) == -1)
			return (-1);
		i++;	
	}
	return (0);	
}

int	ft_get_cmd(t_arg *arg)
{
	int		i;
	char	**cpy;
	t_cmd	cmd;

	i = 0;
	while (arg->cmds[i])
	{
		cpy[i] = ft_strsplit(arg->cmds[i], ' ');
		printf("cpy[%d] = %s\n", i, cpy[i]);
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
