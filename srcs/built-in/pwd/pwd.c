/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:46:35 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 09:36:45 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	pwd(char **path)
{
	int	fd;

	fd = get_fd(path);
	write(fd, getcwd(NULL, 0), ft_strlen(getcwd(NULL, 0)));
	write(fd, "\n", 1);
	return (1);
}

void	main(int argc, char **argv, char **envp)
{
	pwd(0);
}
