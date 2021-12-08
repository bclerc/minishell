/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/01 15:26:44 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env(char *path)
{
	t_env	*env;
	int		fd;

	fd = get_fd(path);
	env = core->env;
	while (env)
	{
		write(fd, env->value, ft_strlen(env->value));
		write(fd, "\n", 1);
		env = env->next;
	}
	return (1);
}
