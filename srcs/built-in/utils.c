/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/17 21:51:11 by bclerc           ###   ########.fr       */
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
		if (access(path, F_OK))
		{
			fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		}
		else
		{
			fd = open(path, O_RDONLY);
			printf("FD successful open\n");
		}
	}
	if (fd < 0)
	{
		printf("Something wrong (error: %d)...\n", fd);
		exit (1);
	}
	return (fd);
}