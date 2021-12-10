/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/10 18:19:47 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	echo(char *str, char *path, int flag_n)
{
	int fd;
	(void)flag_n;
	fd = get_fd(path);
	if (fd <= 0)
		return (0);
	if (str)
		write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	if (fd > 1)
		close(fd);
	return (1);
}
