/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/11 21:16:02 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	change_old_pwd(void)
{
	char	*path;
	char	*tmp;
	char	*ret;

	path = getcwd(NULL, 0);
	tmp = ft_strdup("OLDPWD=");
	if (!tmp)
		return (-1);
	del_env_variable("OLDPWD");
	ret = ft_strjoin(tmp, path);
	if (!ret)
		return (-1);
	add_env_variable(ret);
	free(ret);
	free(tmp);
	free(path);
	return (1);
}

int	change_pwd(void)
{
	char	*path;
	char	*tmp;
	char	*ret;

	path = getcwd(NULL, 0);
	tmp = ft_strdup("PWD=");
	if (!tmp)
		return (-1);
	del_env_variable("PWD");
	ret = ft_strjoin(tmp, path);
	if (!ret)
		return (-1);
	add_env_variable(ret);
	free(ret);
	free(tmp);
	free(path);
	return (1);
}

char	*get(char *path)
{
	char	*home;

	if (path == 0)
	{
		if (get_env_variable("HOME") == NULL)
			home = ft_strdup(getcwd(0, 0));
		else
			home = ft_strdup(get_env_variable("HOME"));
	}
	else if (path[0] == 45)
	{
		if (get_env_variable("OLDPWD") == NULL)
			home = ft_strdup(getcwd(0, 0));
		else
			home = ft_strdup(get_env_variable("OLDPWD"));
	}
	else
		home = ft_strdup(path);
	return (home);
}

void	change_directory(char *path)
{
	change_old_pwd();
	chdir(path);
	change_pwd();
}

int	cd(char *path)
{
	struct stat	t_sb;
	char		*home;
	int			stats;

	home = get(path);
	if (!home)
		return (1);
	stats = stat(home, &t_sb);
	if (stats == 0 && S_ISDIR(t_sb.st_mode))
	{
		if (access(home, W_OK & R_OK) == -1)
		{
			printf("cd: cannot access directory '%s': Permission denied\n",
				path);
			free(home);
			return (126);
		}
		change_directory(home);
	}
	else if (path == NULL)
	{
		home = ft_strdup(get_env_variable("HOME"));
		change_directory(home);
	}
	else
	{
		printf("cd: no such file or directory: %s\n", home);
		free(home);
		return (1);
	}
	free(home);
	return (0);
}
