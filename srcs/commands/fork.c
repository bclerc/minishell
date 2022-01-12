/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:18:03 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 16:25:35 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_forkable(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->cmd, "unset") == 0 && cmd->msg != NULL)
		|| ft_strcmp(cmd->cmd, "export") == 0 && cmd->msg != NULL)
		return (0);
	return (1);
}

int	execute(t_cmd *tmp, int i, int nbpipe, int *pipes)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	core->child_exist = 1;
	core->child = pid;
	if (pid == 0)
	{
		set_in_out(pipes, tmp, i, nbpipe);
		close_fd(pipes, nbpipe);
		ret = execute_commands(tmp);
	}
}

int	fork_cmd(int *pipes, t_cmd *cmd, int nbpipe)
{
	t_cmd	*tmp;
	int		i;
	int		ret;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "exit") == 0)
		{
			if (!tmp->next)
				return (0);
			else
				tmp = tmp->next;
		}
		if (is_forkable(tmp))
		{
			ret = execute(tmp, i, nbpipe, pipes);
			i = i + 2;
		}
		else
			ret = execute_commands(tmp);
		tmp = tmp->next;
	}
	return (ret);
}
