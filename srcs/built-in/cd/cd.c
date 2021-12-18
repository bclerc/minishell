/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/18 18:43:50 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	change_old_pwd(void)
{
	char *path;
	char *tmp;

	path = getcwd(NULL, 0);
	tmp = ft_strdup("OLDPWD=");
	del_env_variable("OLDPWD");
	add_env_variable(ft_strjoin(tmp, path));
	free(tmp);
	free(path);

	return (1);
}

char	*get_home(void)
{
	return (get_env_variable("HOME"));
}

char	*get_oldpwd(void)
{
	return (get_env_variable("OLDPWD"));
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

char *get(char *path)
{
	char *home;

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

int	cd(char *path)
{
	struct stat t_sb;
	char	*home;
	int		stats;

	home = get(path);
	if (!home)
		return (-1);
	stats = stat(home, &t_sb);
	if (stats == 0 && S_ISDIR(t_sb.st_mode))
	{
		if (access(home, W_OK & R_OK) == -1)
		{
			printf("cd: cannot access directory '%s': Permission denied (cheh)\n", path);
			return (1);
		}
		change_old_pwd();
		chdir(home);
		change_pwd();			
	}
	else if (path == NULL)
	{
		change_old_pwd();
		chdir(ft_strdup(get_env_variable("HOME")));
		change_pwd();		
	}
	else
	{
		printf("cd: no such file or directory: %s\n", home);
		free(path);
		return (1);
	}
	free(path);
	return (1);
}
