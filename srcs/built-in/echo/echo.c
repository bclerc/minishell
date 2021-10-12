/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 10:48:40 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INCLUDE ICI, POUR L 'INSTANT J AJOUTE SANS PH

#include "../../../include/minishell.h"

int	echo(char *str, char *path, int flag_n)
{
	int fd;
	fd = get_fd(path);
	write(fd, str, ft_strlen(str));
	if (fd > 1)
		close(fd);
}
