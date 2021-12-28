/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:43:44 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:27:08 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*random_name(void)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_itoa(getpid());
	if (!str)
		return (NULL);
	str[0] = '.';
	str[1] = 'M';
	tmp = ft_strjoin("/tmp/", str);
	free(str);
	return (tmp);
}

int	get_heredoc_fd(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	heredoc_read(int fd, char *eof)
{
	char	*str;
	int		status;

	status = 1;
	while (status)
	{	
		str = readline("> ");
		if (ft_strcmp(str, eof) == 0)
		{
			status = 0;
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

char	*heredoc(t_cmd *cmd)
{
	char	*tmp_file;
	int		fd;

	tmp_file = random_name();
	if (!tmp_file)
		return (NULL);
	fd = get_heredoc_fd(tmp_file);
	if (fd < 0)
	{
		free(tmp_file);
		return (NULL);
	}
	heredoc_read(fd, cmd->redir->fd_in);
	close(fd);
	return (tmp_file);
}
