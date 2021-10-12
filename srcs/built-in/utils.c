/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 15:34:26 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	copy_env(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->export = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
	{
		env->export[i] = ft_strdup(envp[i]);
		i++;
	}
	env->export[i] = 0;
	return (1);
}

int get_fd(char *path)
{
	int fd;
	struct stat buffer;

	fd = 1;
	if (path)
	{
		if (stat(path, &buffer) == 0)
			fd = open(path, O_WRONLY);
		else
			fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	if (fd < 0)
	{
		printf("Something wrong (error: %d)...\n", fd);
		exit (1);
	}
	return (1);
}