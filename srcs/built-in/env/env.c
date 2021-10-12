/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 11:37:06 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env(char **envp, char *path)
{
	char	**env;
	int		fd;
	int		i;

	if (!envp)
		return (0);
	i = 0;
	fd = get_fd(path);
	env = envp;
	while (env[i])
	{
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (1);
}
