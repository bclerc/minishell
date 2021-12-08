/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:09:05 by astrid            #+#    #+#             */
/*   Updated: 2021/11/07 17:31:01 by astrid           ###   ########.fr       */
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
				if (tmp[i][j] != 'n')
				ft_print("Error in specification\n", -1);
					return (NULL);
				// + faire une fct qui sort 
				j++;
			}
			tmp[i] = "-n";
			i++;
			while (ft_strcmp(tmp[i], "-n") == 0)
			{
				tmp[i] = NULL;
				i++;
			}
			
		}
	}
	return (str);
}