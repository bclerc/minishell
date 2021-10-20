/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/20 15:40:25 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_echo(char **cpy, int i, t_cmd *cmd)
{
	int	j;

	j = 0;
	//ft_bzero(cmd, sizeof(t_cmd));
	cmd->nb = i;
	cmd->cmd = ft_strdup(cpy[j]);
	//printf("arg = %p cmd = %p\n", &arg->cmds[i], &cmd->arg);
	j++;
	if (cpy[j])
	{
		if (ft_strncmp(cpy[j], "-n", 2) == 0)
		{
			if (ft_check_n(cpy, cmd, j) == -1 )
				return (-1);
			j++;
			if (cpy[j])
				ft_echo_msg(cpy, j, cmd);
			else if (!cpy[j])
				return (ft_print("\n", -1) & -1);
		}
		else
			j = ft_echo_msg(cpy, j, cmd);
		//printf("cmds[%i] = %s\n", i + 1, arg->cmds[i + 1]);
		// if (i == -1)
		// 	return (-1);
	}
	if (!cpy[j]) // a modifier : c a faire ne fct de la cmd suivante (donc arg->cmds) si c un | ou des < > 
		cmd->std = 0; // pour executer de suite 
	printf("echo : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
	cmd = cmd->next;
	return (j);
}

int	ft_echo_msg(char **cpy, int i, t_cmd *cmd)
{
	if (!cpy[i])
		return (ft_print("\n", -1));
	cmd->msg = ft_strdup(cpy[i]);
	i++;
	//printf("i_msg= %d\n", i);
	return (i);
}

int	ft_check_n(char **cpy, t_cmd *cmd, int i)
{
	int j;

	j = 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] != 'n')
			ft_print("Error in specification\n", -1);
		j++;
	}
	cmd->spec = "-n";
	return (0);
}