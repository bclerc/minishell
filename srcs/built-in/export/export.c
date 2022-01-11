/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 17:43:00 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	export_add(char *argv)
{
	char	**args;
	int		b;

	if (!ft_strchr(argv, '='))
		return (0);
	args = ft_strsplit(argv, ' ');
	b = 0;
	while (args[b])
	{
		del_env_variable(args[b]);
		add_env_variable(args[b]);
		b++;
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
		return (export_add(path));
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
