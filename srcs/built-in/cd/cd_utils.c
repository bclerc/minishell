/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:55:56 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 15:57:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	have_access(char *home, char *path)
{
	if (access(home, W_OK & R_OK) == -1)
	{
		printf("cd: cannot access directory '%s': Permission denied\n", path);
		free(home);
		return (0);
	}
	return (1);
}
