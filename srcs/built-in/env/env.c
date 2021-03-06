/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 16:47:34 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env(char *path)
{
	t_env	*env;
	int		fd;

	(void)path;
	fd = 0;
	env = g_core->env;
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	exit(EXIT_SUCCESS);
}
