/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:46:35 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 13:00:59 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	pwd(char *path)
{
	char	*pwd;
	int		fd;

	fd = get_fd(path, 0);
	pwd = getcwd(0, 0);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	exit(EXIT_SUCCESS);
}
