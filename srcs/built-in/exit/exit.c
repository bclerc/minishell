/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:48:32 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 17:35:10 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check(char **argv)
{
	int	status;

	status = 0;
	if (argv[1])
	{
		printf("minishell: exit: to many arguments\n");
		status = 1;
	}
	else if (!ft_strisdigit(argv[0]))
	{
		printf("minishell: exit : %s : numeric argument required\n", argv[0]);
		status = 1;
	}
	return (status);
}

int	builtin_exit(t_cmd *cmd, int status)
{
	char	**argv;
	int		tmp;

	if (!cmd->msg)
		return (status - 300);
	argv = ft_strsplit(cmd->msg, ' ');
	tmp = check(argv);
	if (!tmp)
	{
		tmp = ft_atoi(argv[0]);
		if (tmp > 255 || tmp < 0)
			status = 255 - 300;
		else
			status = tmp - 300;
	}
	else
		status = tmp;
	rm_split(argv);
	return (status);
}
