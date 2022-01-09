/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/08 18:09:39 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*read_folder(DIR *pdir, char *path, t_cmd *cmd)
{
	struct dirent	*pdirent;
	char			*tmp;
	char			*ret;

	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		if (ft_strcmp(cmd->cmd, pdirent->d_name) == 0)
		{
			closedir(pdir);
			tmp = ft_strjoin(path, "/");
			ret = ft_strjoin(tmp, cmd->cmd);
			free(tmp);
			return (ret);
		}
		pdirent = readdir(pdir);
	}
	return (NULL);
}

char	*get_executable_path(t_cmd *cmd)
{
	DIR				*pdir;
	char			**path;
	char			*ret;
	int				i;

	path = ft_strsplit(get_env_variable("PATH"), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		pdir = opendir(path[i]);
		if (pdir != NULL)
		{
			ret = read_folder(pdir, path[i], cmd);
			if (ret)
			{
				rm_split(path);
				return (ret);
			}
		}
		i++;
	}
	rm_split(path);
	return (cmd->cmd);
}

int	exec(t_cmd *cmd)
{
	char	*path;
	char	**argv;
	char	**tab_env;
	int		status;
	int		i;

	status = 1;
	i = -1;
	core->child_exist = 1;
	argv = get_argv(cmd);
	tab_env = env_to_char();
	path = get_executable_path(cmd);
	if ((status = execve(path, argv, tab_env)) < 0)
	{
		printf("%s: command not found\n", cmd->cmd);
		exit(127);
	}
	rm_split(argv);
	rm_split(tab_env);
	core->child_exist = 0;
	return (status);
}

int	execute_commands(t_cmd *cmd)
{
	int	ret;
	ret = 1;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ret = cd(cmd->msg);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		(env(NULL));
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		(export(NULL, cmd->msg));
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		(pwd(cmd->msg));
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		unset(cmd->msg);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		write(1, "exit 😱 😭\n", 16);
		return (-1);
	}
	else
		ret = exec(cmd);
	return (ret);
}
