/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:26 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:41:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset(char *var)
{
	char	**vars;
	int		i;

	if (!var)
		return (-1);
	vars = ft_strsplit(var, ' ');
	if (!vars)
		return (-1);
	i = 0;
	while (vars[i])
	{
		del_env_variable(vars[i]);
		i++;
	}
	rm_split(vars);
	return (1);
}
