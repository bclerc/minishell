/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 13:44:56 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*new;

	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = ft_fill_echo1(new, arg, cpy);
	if (!new)
		return (NULL);
	if (cpy[arg->j])
		new = ft_fill_echo2(cpy, arg, new);
	if (!new)
		return (NULL);
	new->std = ft_fill_echostd(arg, new);
	new->next = NULL;
	if (tmp == NULL)
	{
		new->prev = NULL;
		tmp = new;
	}
	else
		cmd = ft_cmd_builtin(cmd, tmp, new);
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
	arg->spec_n = 1;
	return (0);
}

t_cmd	*ft_fill_echo1(t_cmd *new, t_arg *arg, char **cpy)
{
	int		tmp_nb;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	tmp_nb = arg->i_cpy;
	new->redir = NULL;
	new->msg = NULL;
	new->spec = NULL;
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->builtin = 1;
	new->cmd = ft_strdup(cpy[arg->j]);
	if (!new->cmd)
		return (NULL);
	arg->j++;
	return (new);
}

t_cmd	*ft_fill_echo2(char **cpy, t_arg *arg, t_cmd *new)
{
	if (ft_strncmp(cpy[arg->j], "-", 1) == 0)
	{
		if (ft_check_n(cpy, arg->j, arg, new) == 1)
			return (NULL);
		arg->j++;
		if (cpy[arg->j])
		{
			new->msg = ft_strdup(ft_cpy_msg(arg, cpy, arg->j, new));
			if (!new->msg)
				return (NULL);
		}	
	}
	else
	{
		new->spec = NULL;
		new->msg = ft_strdup(ft_cpy_msg(arg, cpy, arg->j, new));
		if (!new->msg)
			return (NULL);
	}
	return (new);
}

int	ft_fill_echostd(t_arg *arg, t_cmd *new)
{
	if (arg->i_cpy == arg->count - 1)
		new->std = 0;
	else if (arg->i_cpy < arg->count)
		new->std = ft_std(arg, arg->i_cpy + 1);
	return (new->std);
}
