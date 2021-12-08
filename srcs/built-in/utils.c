/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/16 17:12:55 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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