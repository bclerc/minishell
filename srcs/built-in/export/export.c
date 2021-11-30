/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/30 15:18:26 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int add_env_variable(char *var)
{
	return (1);
}
int	export_add(char *argv)
{
	int		i, b;
	int		length;
	char 	**args;
	char	**tmp;

	getchar();
	args = ft_strsplit(argv, ' ');
	getchar();
	length = get_env_length(core.envp) + get_env_length(args);
	tmp = malloc(sizeof(char*) * length);
	i = 0;
	while (core.envp[i])
	{
		tmp[i] = ft_strdup(core.envp[i]);
		i++;
	}
	b = 0;
	while (args[b])
	{
		tmp[i + b] = ft_strdup(args[b]);
		b++;
	}
	getchar();
	tmp[i + b] = 0;
	printf("Malloced %d bytes and writted %d bytes\n",length, i + b);
	getchar();
	i = 0;
	while (tmp[i])
	{
		printf("Line %d : %s\n", i, tmp[i]);
		i++;
	}
	change_env(tmp);
	return (1);
}

int	export(char *path, char *args)
{
	char	**env;
	char	*tmp;
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
		printf("Ligne %d : %s\n", i, core.envp[i]);
		// write(fd, "declare -x ", 11);
		// write(fd, core.envp[i], ft_strlen(core.envp[i]));
		// write(fd, "\n", 1);
		i++;
	}
	printf("Readed %d lines\n", i - 1);
	return (1);
}
