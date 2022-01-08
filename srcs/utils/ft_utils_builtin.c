/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:06:28 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/07 17:17:57 by asgaulti         ###   ########.fr       */
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
		new->msg = ft_cpy_msg(arg, cpy, j, new);
		if (!new->msg)
			return (NULL);
	}
	new->spec = NULL;
	new->next = NULL;
	return (new);
}
