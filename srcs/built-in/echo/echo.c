/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/11 12:00:48 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE ICI, POUR L 'INSTANT J AJOUTE SANS PH

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	echo(char *str, char *path, int flag_n)
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
	write(fd, str, ft_strlen(str));
	if (fd > 1)
		close(fd);
}

int main(int argc, char **argv)
{
	echo(argv[1], argv[2][0] == '0' ? 0 : argv[2], 0);
}