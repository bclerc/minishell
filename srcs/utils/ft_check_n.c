/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:09:05 by astrid            #+#    #+#             */
/*   Updated: 2022/01/11 21:13:23 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_n(char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	if (ft_strcmp(tmp[i], "echo") == 0)
	{
		i++;
		if (ft_strcmp(tmp[i], "-n") == 0)
		{
			j = 0;
			while (tmp[i][j])
			{
				if (tmp[i][j++] != 'n')
					return (ft_print("Error in specification\n", -1) && NULL);
			}
			tmp[i++] = "-n";
			while (ft_strcmp(tmp[i], "-n") == 0)
				tmp[i++] = NULL;
		}
	}
	return (str);
}
