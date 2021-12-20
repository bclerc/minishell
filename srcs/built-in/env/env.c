/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/20 13:17:02 by bclerc           ###   ########.fr       */
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
		printf("%s\n", env->value);
		env = env->next;
	}
	exit(EXIT_SUCCESS);
	return (1);
}
