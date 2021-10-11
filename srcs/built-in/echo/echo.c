/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/11 12:23:05 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE ICI, POUR L 'INSTANT J AJOUTE SANS PH

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_fd(char *path);

int ft_strlen(char *str);

int	echo(char *str, char *path, int flag_n)
{
	int fd;
	fd = get_fd(path);
	write(fd, str, ft_strlen(str));
	if (fd > 1)
		close(fd);
}

int main(int argc, char **argv)
{
	echo(argv[1], argv[2][0] == '0' ? 0 : argv[2], 0);
}