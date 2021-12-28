/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:42:57 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_eof(char *s)
{
	int	i;

	i = 0;
	while (s[i] != -1)
		i++;
	if (s[i] == -1)
		return (1);
	return (0);
}

int	get_fd(char *path)
{
	struct stat	buffer;
	int			fd;

	fd = 1;
	if (path)
	{
		if (access(path, F_OK))
			fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		else
			fd = open(path, O_RDONLY);
	}
	if (fd < 0)
	{
		printf("Something wrong (error: %d)...\n", fd);
		exit (1);
	}
	return (fd);
}
