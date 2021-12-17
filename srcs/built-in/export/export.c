/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/14 17:27:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int	export_add(char *argv)
{
	int		b;
	char 	**args;

	args = ft_strsplit(argv, ' ');
	b = 0;
	while (args[b])
	{
		add_env_variable(args[b]);
		b++;
	}
	return (1);
}

int	export(char *path, char *args)
{
	t_env 	*env;
	int		fd;
	int		i;

	(void)path;
	if (args)
	{
		if (export_add(args) == -1)
			return (-1);
	}
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
	return (1);
}
