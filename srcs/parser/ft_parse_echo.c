/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/12/29 18:11:02 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd)
{
	int		j;
	int		tmp_nb;
	t_cmd	*tmp;
	t_cmd	*tmp2;
	t_cmd	*new;

	j = 0;
	tmp_nb = arg->i_cpy;
	tmp = cmd;
	tmp2 = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->builtin = 1;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	if (cpy[j])
	{
		if (ft_strncmp(cpy[j], "-", 1) == 0)
		{
			if (ft_check_n(cpy, j, arg, new) == 1)
				return (NULL);
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
	new->next = NULL;
	if (tmp == NULL)
	{
		new->previous = NULL;
		tmp = new;
	}
	else
	{
		cmd->next = new;
		if (tmp2->next != NULL)
		{
			while (tmp2->next->next != NULL)
			{
				tmp2 = tmp2->next;
				
			}		
			new->previous = tmp2;
		}
		// if (new->previous->std > 2 && new->previous->std <= 5)
		// 	new = ft_redir(new);
		cmd = new;
	}
	//printf("new1 = %s msg = %s std = %d\n", tmp->cmd, tmp->msg, tmp->std);
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
