/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/15 12:43:30 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *transform_str(char *str, char **envp)
{
	int i;
	char **split;

	split = ft_split(str, "$");
	i = 0;
	while (split[i])
	{
		i++;
	}
}