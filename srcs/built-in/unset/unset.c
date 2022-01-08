/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:26 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/08 14:12:21 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset(char *var)
{
	char	**vars;
	int		i;

	if (!var)
		exit(EXIT_FAILURE);
	vars = ft_strsplit(var, ' ');
	if (!vars)
		exit(EXIT_FAILURE);
	i = 0;
	while (vars[i])
	{
		del_env_variable(vars[i]);
		i++;
	}
	rm_split(vars);
	exit(EXIT_SUCCESS);
}
