/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:43:44 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 17:46:05 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	random_char(void)
{
	char	*buff[4];
	int		fd;
	int		value;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (-1);
	read(fd, buff, 4);
	value = *(int *)buff;
	close(fd);
	if (value < 0)
		value = -value;
	return ('a' + value % 26);
}

char	*random_name(void)
{
	char	*random_str;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	path = "/tmp/.shell_\0";
	random_str = malloc(sizeof(char) * 8);
	if (!random_str)
		return (NULL);
	while (i < 7)
	{
		random_str[i] = random_char();
		i++;
	}
	random_str[i] = '\0';
	tmp = ft_strjoin(path, random_str);
	free(random_str);
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
		if (!str || ft_strcmp(str, eof) == 0)
		{
			status = 0;
			break ;
		}
		add_history(str);
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
