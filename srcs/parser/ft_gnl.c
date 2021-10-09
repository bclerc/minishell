/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:35:29 by asgaulti          #+#    #+#             */
/*   Updated: 2021/01/05 17:36:18 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_static(char *str, char buf[BUF_SIZE], int len)
{
	char	*tmp;

	buf[len] = '\0';
	if (!str)
		str = ft_strdup(buf);
	else if (str)
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	return (str);
}

char	*ft_write_line(char *str, char **line)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\n' && str[i])
		i++;
	if (i < len)
	{
		*line = ft_substr(str, 0, i);
		tmp = str;
		str = ft_substr(str, i + 1, len);
		free(tmp);
	}
	else
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int		get_next_line(int fd, char **line)
{
	int				len;
	char			buf[BUF_SIZE + 1];
	static char		*str;

	if (fd < 0 || !line || BUF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	while ((len = read(fd, buf, BUF_SIZE)) > 0)
	{
		str = ft_get_static(str, buf, len);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	str = ft_write_line(str, line);
	if (!str)
		return (0);
	return (1);
}
