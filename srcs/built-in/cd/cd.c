/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/04 15:21:16 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	change_old_pwd(void)
{
	char	*path;
	char	*tmp;

	path = getcwd(NULL, 0);
	tmp = ft_strdup("OLDPWD=");
	del_env_variable("OLDPWD");
	add_env_variable(ft_strjoin(tmp, path));
	free(tmp);
	free(path);
	return (1);
}

int	change_pwd(void)
{
	char	*path;
	char	*tmp;

	path = getcwd(NULL, 0);
	tmp = ft_strdup("PWD=");
	del_env_variable("PWD");
	add_env_variable(ft_strjoin(tmp, path));
	free(path);
	free(tmp);
	return (1);
}

char	*get(char *path)
{
	char	*home;

	if (path == 0)
	{
		if (get_env_variable("HOME") == NULL)
			home = getcwd(0, 0);
		else
			home = get_env_variable("HOME");
	}
	else if (path[0] == 45)
	{
		if (get_env_variable("OLDPWD") == NULL)
			home = getcwd(0, 0);
		else
			home = get_env_variable("OLDPWD");
	}
	else
		home = path;
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
		return (-1);
	stats = stat(home, &t_sb);
	if (stats == 0 && S_ISDIR(t_sb.st_mode))
	{
		if (access(home, W_OK & R_OK) == -1)
		{
			printf("cd: cannot access directory '%s': Permission denied\n",
				path);
			return (1);
		}
		change_directory(home);
	}
	else if (path == NULL)
		change_directory(ft_strdup(get_env_variable("HOME")));
	else
		printf("cd: no such file or directory: %s\n", home);
	return (1);
}
