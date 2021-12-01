/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:26 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/01 15:31:35 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int	unset(char *var)
{
	char	**tmp;
	char	**vars;
	int		length;
	int		i;
	int		b;

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
	return (1);
}