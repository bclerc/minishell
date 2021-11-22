/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/17 15:37:40 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	change_old_pwd(void)
{
	char *path;
	char *tmp;
	int i;

	i = 0;
	while (core.envp[i])
	{
		if (core.envp[i][0] == 'O' && core.envp[i][1] == 'L' && core.envp[i][2] == 'D'
			&& core.envp[i][3] == 'P' && core.envp[i][4] == 'W' && core.envp[i][5] == 'D')
			break ;
		i++;
	}
	path = getcwd(NULL, 0);
	tmp = ft_strdup("OLDPWD=");
	core.envp[i] = ft_strjoin(tmp, path);
	free(tmp);
	free(path);
	return i;
}

char	*get_home(void)
{
	char	*path;
	char	*tmp;
	int		find;
	int		i;

	i = 0;
	find = 0;
	while (core.envp[i])
	{
		if (core.envp[i][0] == 'H' && core.envp[i][1] == 'O' && core.envp[i][2] == 'M'
			&& core.envp[i][3] == 'E' && core.envp[i][4] == '=')
		{
			find = 1;
			break ;
		}
		i++;
	}
	if (!find)
	{
		printf("cd: home directory not set");
		exit(0);
	}
	path = ft_strdup(&core.envp[i][5]);
	return path;
}

char	*get_oldpwd(void)
{
	char	*path;
	char	*tmp;
	int		find;
	int		i;

	i = 0;
	find = 0;
	while (core.envp[i])
	{
		if (core.envp[i][0] == 'O' && core.envp[i][1] == 'L' && core.envp[i][2] == 'D'
			&& core.envp[i][3] == 'P' && core.envp[i][4] == 'W' && core.envp[i][5] == 'D'
			&& core.envp[i][6] == '=')
		{
			find = 1;
			break ;
		}
		i++;
	}
	if (!find)
	{
		printf("cd: old working directory not set");
		exit(0);
	}
	path = ft_strdup(&core.envp[i][5]);
	return (path);
}

int	change_pwd(void)
{
	char	*path;
	char	*tmp;
	int 	find;
	int		i;

	i = 0;
	find = 0;
	while (core.envp[i])
	{
		if (core.envp[i][0] == 'P' && core.envp[i][1] == 'W' && core.envp[i][2] == 'D')
		{
			find = 1;
			break ;
		}
		i++;
	}
	path = getcwd(NULL, 0);
	tmp = ft_strdup("PWD=");
	core.envp[i] = ft_strjoin(tmp, path);
	free(path);
	free(tmp);
	return (i);
}


int	cd(char *path)
{
	struct stat t_sb;
	char		*home;
	int i;
	int			stats;
	stats = stat(path, &t_sb);
	if (stats == 0 && S_ISDIR(t_sb.st_mode))
	{
		if (access(path, W_OK && R_OK) == -1)
		{
			printf("cd: cannot access directory '%s': Permission denied (cheh)\n", path);
			return (1);
		}
		change_old_pwd();
		chdir(path);
		i = change_pwd();			
	}
	else if (path == NULL)
	{
		i = change_pwd();		
		home = get_home();
		chdir(home);
		free(home);
		change_old_pwd();
	}
	else
	{
		printf("cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (1);
}
