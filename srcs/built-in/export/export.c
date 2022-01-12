/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 15:48:55 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	export_add(char *argv)
{
	char	**args;
	char	*tmp;
	char	*value;
	int		b;
	int		i;

	printf("ARGV= %s\n", argv);
	if (!ft_strchr(argv, '='))
		return (0);
	args = ft_strsplit_s(argv, "$=");
	b = 0;
	i = 0;
	while (args[b])
	{
		tmp = ft_strjoin(args[b], "=");
		value = ft_strjoin(tmp, args[b + 1]);
		printf("VALUE  : %s\n", value);
		free(tmp);
		free(value);
		printf("ARG: %s\n", args[b]);
		b += 2;
	}
	rm_split(args);
	return (1);
}

int	export(char *path, char *args)
{
	t_env	*env;
	int		fd;
	int		i;

	(void)path;
	if (args)
		return (export_add("lol$=mdr frere$   lol=frere"));
	i = 0;
	fd = 1;
	env = core->env;
	while (env)
	{
		write(fd, "declare -x ", 11);
		write(fd, env->value, ft_strlen(env->value));
		write(fd, "\n", 1);
		env = env->next;
	}
	if (!args)
		exit(EXIT_SUCCESS);
	return (1);
}
