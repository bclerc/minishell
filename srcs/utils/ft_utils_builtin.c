/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:11:09 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 21:11:39 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_fill_builtin(char **cpy, t_cmd *new, t_arg *arg)
{
	int	tmp_nb;
	int	j;

	tmp_nb = 0;
	j = 0;
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->builtin = 1;
	new->cmd = ft_strdup(cpy[j]);
	if (!new->cmd)
		return (NULL);
	j++;
	ft_fill_std(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
	{
		new->msg = ft_strdup(ft_cpy_msg(arg, cpy, j, new));
		if (!new->msg)
			return (NULL);
	}
	new->spec = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_fill_other(char **cpy, t_cmd *new, t_arg *arg)
{
	char	*test;
	int		tmp_nb;
	int		j;

	tmp_nb = 0;
	j = 0;
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->builtin = 0;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	ft_fill_std(arg, new);
	if (!cpy[j])
		new->msg = NULL;
	else
	{
		test = ft_cpy_msg(arg, cpy, j, new);
		new->msg = ft_strdup(test);
	}
	new->spec = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_cmd_builtin(t_cmd *cmd, t_cmd *tmp, t_cmd *new)
{
	cmd->next = new;
	if (tmp->next != NULL)
	{
		while (tmp->next->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
	}
	cmd = new;
	return (cmd);
}
