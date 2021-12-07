/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/06 10:53:59 by bclerc           ###   ########.fr       */
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


int	cd(char *path)
{
	struct stat t_sb;
	char		*home;
	int i;
	int			stats;

	if (path[0] == 45)
		home = ft_strdup(get_env_variable("OLDPWD"));
	else
		home = ft_strdup(path);
	if (!home)
		return (-1);
	usleep(50);
	stats = stat(home, &t_sb);
	if (stats == 0 && S_ISDIR(t_sb.st_mode))
	{
		if (access(home, W_OK && R_OK) == -1)
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
