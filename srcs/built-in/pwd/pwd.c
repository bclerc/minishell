/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:46:35 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:40:29 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	pwd(char *path)
{
	char	*pwd;
	int		fd;

	fd = get_fd(path);
	pwd = getcwd(NULL, 0);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	return (1);
}
