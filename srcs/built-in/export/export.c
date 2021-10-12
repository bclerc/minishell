/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 15:34:19 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int	export(char **envp, char *path)
{
	char	**env;
	int		fd;
	int		i;

	if (!envp)
		return (0);
	i = 0;
	fd = get_fd(path);
	env = envp;
	export_sort(env, get_env_lenght(env));
	while (env[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
	// AJOUTER ENV quand on copy lol;
	return (1);
}
