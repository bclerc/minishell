/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/25 11:23:11 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int	export_add(char **envp, char **args)
{
	int i;

	while (args[i])
	{
		add_env_variable(envp, args[i]);
		i++;
	}
	return (1);
}

int	export(char **envp, char *path, char **args)
{
	char	**env;
	int		fd;
	int		i;

	if (!envp)
		return (0);
	args++;
	if (args)
		export_add(envp, args);
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
	return (1);
}
