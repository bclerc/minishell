/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:09:19 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 21:16:44 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_value_to_stack(t_cmd *stack, t_cmd *stack2)
{
	t_cmd	*tmp;

	tmp = stack2;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = stack;
	return (1);
}

t_cmd	*dup_cmd(t_cmd *cmd)
{
	t_cmd	*list;
	t_cmd	*tmp;
	t_cmd	*last;
	int		i;

	tmp = cmd;
	last = cmd;
	while (tmp)
	{
		if (tmp->cmd == NULL)
		{
			last->next = tmp->next;
			tmp = last;
			continue ;
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (cmd);
}

int	get_pipe_count(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	if (!cmd)
		return (-1);
	tmp = cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i - 1);
}

int	close_fd(int *tab_fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes * 2)
	{
		close(tab_fd[i]);
		i++;
	}
	return (1);
}

int	open_pipe(int *tab_fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		pipe(tab_fd + i * 2);
		i++;
	}
	return (1);
}
