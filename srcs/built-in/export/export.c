/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/16 16:57:47 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int	export_add(char *argv)
{
	int i;
	char **args;

	args = ft_strsplit(argv, " ");
	i = 0;
	while (args[i])
	{
		add_env_variable(args[i]);
		i++;
	}
	return (1);
}

int	export(char *path, char *args)
{
	char	**env;
	int		fd;
	int		i;

	if (!core.envp)
		return (0);
	if (args)
		export_add(args);
	i = 0;
	fd = get_fd(path);
	env = core.envp;
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
