/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:13:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 16:55:21 by asgaulti         ###   ########.fr       */
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

int	mul_redir(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redir;
	while (tmp)
	{
		if (!tmp->next)
			fd = get_fd(tmp->fd_out, tmp->std_redir);
		else
		{
			fd = get_fd(tmp->fd_out, tmp->std_redir);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	get_fd(char *path, int append)
{
	struct stat	buffer;
	int			fd;

	fd = 1;
	if (path)
	{
		if (access(path, F_OK))
			fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		else if (append == REDIR_APPEND_OUT)
			fd = open(path, O_RDWR | O_APPEND);
		else if (append == REDIR_OUT)
			fd = open(path, O_RDWR | O_TRUNC);
		else
			fd = open(path, O_RDWR);
	}
	if (fd < 0)
	{
		printf("Something wrong (error: %d) : %s\n", fd, path);
		perror("open: ");
		exit (EXIT_FAILURE);
	}
	return (fd);
}
