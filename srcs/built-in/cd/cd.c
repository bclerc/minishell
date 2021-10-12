/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:44:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 10:13:08 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//
//	JE SAIS PAS TRES JOLIE
//	JE VAIS RANGER DEMAIN PROMIS
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// a bouger
int ft_strlen(char *str);
char *ft_strdup(char *s);
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	int				i;

	if (!n)
		return (0);
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < (int)(n - 1) && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (0);
	while (*s1 != 0)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return (str);
}

// fin a bouger

int	change_old_pwd(char **env)
{
	char *path;
	char *tmp;
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'O' && env[i][1] == 'L' && env[i][2] == 'D'
			&& env[i][3] == 'P' && env[i][4] == 'W' && env[i][5] == 'D')
			break ;
		i++;
	}
	path = getcwd(NULL, 0);
	tmp = ft_strdup("OLDPWD=");
	env[i] = ft_strjoin(tmp, path);
	free(tmp);
	free(path);
	return i;
}

char	*get_home(char **env)
{
	char	*path;
	char	*tmp;
	int		find;
	int		i;

	i = 0;
	find = 0;
	while (env[i])
	{
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M'
			&& env[i][3] == 'E' && env[i][4] == '=')
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
	path = ft_strdup(&env[i][5]);
	return path;
}

char	*get_oldpwd(char **env)
{
	char	*path;
	char	*tmp;
	int		find;
	int		i;

	i = 0;
	find = 0;
	while (env[i])
	{
		if (env[i][0] == 'O' && env[i][1] == 'L' && env[i][2] == 'D'
			&& env[i][3] == 'P' && env[i][4] == 'W' && env[i][5] == 'D'
			&& env[i][6] == '=')
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
	path = ft_strdup(&env[i][5]);
	return path;
}

int	change_pwd(char **env)
{
	char	*path;
	char	*tmp;
	int 	find;
	int		i;

	i = 0;
	find = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
		{
			find = 1;
			break ;
		}
		i++;
	}
	path = getcwd(NULL, 0);
	tmp = ft_strdup("PWD=");
	env[i] = ft_strjoin(tmp, path);
	free(path);
	free(tmp);
	return (i);
}


int	cd(char **env, char *path)
{
	struct stat t_sb;
	char		*home;
	int i;
	
	if (stat(path, &t_sb) == 0 && S_ISDIR(t_sb.st_mode))	
	{
		change_old_pwd(env);
		chdir(path);
		i = change_pwd(env);			
	}
	else if (path == NULL)
	{
		change_old_pwd(env);
		home = get_home(env);
		chdir(home);
		free(home);
		i = change_pwd(env);		
	}
	else
	{
		printf("cd: no such file or directory: %s\n", path);
		exit(0);
	}
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int i;

	printf("new path : %s\n", envp[i = cd(envp, argv[1])]);
	free(envp[i]); // STIL REACHABLE
}