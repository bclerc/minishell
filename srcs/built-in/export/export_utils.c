/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:05:05 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/01 15:39:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void	export_sort(char **value, int len)
{
	char	*tmp;
	int		i;

	tmp = 0;
	i = 0;
	i = 0;
	while (i < len - 1)
	{
		if (value[i][0] <= value[i + 1][0])
			i++;
		else
		{
			tmp = value[i];
			value[i] = value[i + 1];
			value[i + 1] = tmp;
			i = 0;
		}
	}
}
