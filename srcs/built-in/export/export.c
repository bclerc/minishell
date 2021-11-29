/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/17 15:32:09 by bclerc           ###   ########.fr       */
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
		if (ft_havechr(args[i], '='))
			add_env_variable(args[i]);
		else
		{
			printf("export: %s is invalide variable\n", args[i]);
			return (-1);
		}
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
	{
		if (export_add(args) == -1)
			return (-1);
	}
	i = 0;
	fd = get_fd(path);
	while (core.envp[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, core.envp[i], ft_strlen(core.envp[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (1);
}
