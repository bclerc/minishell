/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/10 18:20:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env(char *path)
{
	t_env	*env;
	int		fd;

	(void)path;
	fd = 0;
	env = core->env;
	while (env)
	{
		write(0, env->value, ft_strlen(env->value));
		write(0, "\n", 1);
		env = env->next;
	}
	return (1);
}
