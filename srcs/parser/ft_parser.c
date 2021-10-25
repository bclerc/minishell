/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/25 09:54:04 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
int	ft_parser(char *str, char **envp)
{
	int		i;
	t_arg	arg;
	t_cmd	cmd;
	
	i = 0;
	if (ft_get_arg(str, &arg) == -1)
		return (-1);
	// while (arg.cmds[i])
	//  	i++;
	// printf("i = %d\n", i);
	if (ft_init_cmd(&cmd, &arg) < 0)
		return (0);
	i = 0;
	ft_get_cmd(&arg, &cmd);
	// while (arg.cmds[i])
	// {
	// 	puts("che");
	// 	ft_get_cmd(&arg, &cmd);
	// 	// if (ft_get_cmd(&arg, &cmd) == -1)
	// 	// 	return (-1);
	// 	i++;	
	// }
	return (0);	
}

int ft_init_cmd(t_cmd *cmd, t_arg *arg)
{
	ft_bzero(cmd, sizeof(t_cmd));
	return (0);
}

int	ft_get_cmd(t_arg *arg, t_cmd *cmd)
{
	int		i;
	char	**cpy;

	i = 0;
	while (i != arg->count)
	{
		cpy = ft_strsplit_s(arg->cmds[i], ' ');
	 	printf("cmds[%d] = %s\n",i , arg->cmds[i]);
		ft_parse_cmd(arg, cpy, i, cmd);
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
	else
		return (-1);
}
