/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:50:10 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/17 14:47:59 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_check_spec(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if ((*cmd)->std > 1 && (*cmd)->std <= 5)
	{
		while (*cmd/* && (*cmd)->next*/)
		{
			if ((*cmd)->msg == NULL)
				*cmd = (*cmd)->next;
			else if ((*cmd)->msg && (*cmd)->msg[0] == '-')
			{
				tmp->spec = (*cmd)->msg;
				(*cmd)->msg = NULL;
				break;
			}
			*cmd = (*cmd)->next;
		}
	}
	*cmd = tmp;
	return (*cmd);
}
void	ft_spec_out(t_cmd *new, t_arg *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = arg->i_cpy;
	j = 0;
	new->fd_out = ft_strdup(arg->cmds[i + 2]);
	if (!new->fd_out)
		return ;
	//printf("out = %s\n", new->fd_out);
	while (new->fd_out[j])
	{
		if (new->fd_out[j] == '-')
		{
			tmp = ft_strsub(new->fd_out, j, ft_strlen(new->fd_out));
			new->msg = tmp;
			new->fd_out = ft_strsub(new->fd_out, 0,
					ft_strlen(new->fd_out) - ft_strlen(new->msg) - 1);
			//printf("out = %s msg = %s\n", new->fd_out, new->msg);
		}
		j++;
	}
	new->fd_in = NULL;
}

void	ft_spec_in(t_cmd *new, t_arg *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = arg->i_cpy;
	j = 0;
	new->fd_in = ft_strdup(arg->cmds[i + 2]);
	if (!new->fd_in)
		return ;
	while (new->fd_in[j])
	{
		if (new->fd_in[j] == '-')
		{
			tmp = ft_strsub(new->fd_in, j, ft_strlen(new->fd_in));
			new->msg = tmp;
			new->fd_in = ft_strsub(new->fd_in, 0,
					ft_strlen(new->fd_in) - ft_strlen(new->msg) - 1);
			//printf("in = %s msg = %s\n", new->fd_in, new->msg);
		}
		j++;
	}
	new->fd_out = NULL;
}
