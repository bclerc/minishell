/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/12/17 13:32:34 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	int		tmp_nb;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp_nb = arg->i_cpy;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->nb = arg->i_cpy;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	if (cpy[j])
	{
		if (ft_strncmp(cpy[j], "-", 1) == 0)
		{
			if (ft_check_n(cpy, j, arg, new) == 1)
				return (NULL);
			arg->spec_n = new->spec;
			j++;
			if (cpy[j])
			{
				new->msg = ft_cpy_msg(arg, cpy, j, new);
				if (!new->msg)
					return (NULL);
			}	
			else if (!cpy[j])
			{
				new->msg = NULL;
				new->next = NULL;
				if (tmp == NULL)
					tmp = new;
				else
					cmd->next = new;
				return (tmp);
			}
		}
		else
		{
			new->spec = NULL;
			new->msg = ft_cpy_msg(arg, cpy, j, new);
			if (!new->msg)
				return (NULL);
		}	
	}
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, arg->i_cpy + 1);
	if (new->std >= 2 && new->std <= 5)
	{
		ft_fill_fd(arg, new);
	}
	//printf("echo2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %din =%s out = %s\n", new->nb, new->cmd, new->spec, new->msg, new->std, new->fd_in, new->fd_out);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;
	return (tmp);
}

int	ft_check_n(char **cpy, int i, t_arg *arg, t_cmd *new)
{
	int		j;
	char	*tmp;

	j = 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] == 'n')
			arg->n++;
		if (cpy[i][j] != 'n')
		{
			ft_print("Error in specification\n", -1);
			return (1);
		}	
		j++;
	}
	new->spec = "-n";
	return (0);
}
