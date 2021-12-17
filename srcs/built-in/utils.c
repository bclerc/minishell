/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/16 11:32:03 by bclerc           ###   ########.fr       */
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
			fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	}
	if (fd < 0)
	{
		printf("Something wrong (error: %d)...\n", fd);
		exit (1);
	}
	return (fd);
}