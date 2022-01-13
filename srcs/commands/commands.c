/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/13 12:04:55 by bclerc           ###   ########.fr       */
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
			tmp = ft_strjoin(path, "/");
			ret = ft_strjoin(tmp, cmd->cmd);
			free(tmp);
			return (ret);
		}
		pdirent = readdir(pdir);
	}
	return (NULL);
}

char	*return_norm(DIR *pdir, char **path, char *ret)
{
	closedir(pdir);
	rm_split(path);
	return (ret);
}

char	*get_executable_path(t_cmd *cmd)
{
	DIR				*pdir;
	char			**path;
	char			*ret;
	int				i;

	ret = get_env_variable("PATH");
	path = ft_strsplit(ret, ':');
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
				return (return_norm(pdir, path, ret));
		}
		i++;
		closedir(pdir);
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
	g_core->child_exist = 1;
	argv = get_argv(cmd);
	tab_env = env_to_char();
	path = get_executable_path(cmd);
	status = execve(path, argv, tab_env);
	if (status < 0)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, " command not found\n", 19);
		rm_split(argv);
		rm_split(tab_env);
		exit(127);
	}
	rm_split(argv);
	rm_split(tab_env);
	g_core->child_exist = 0;
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
		(pwd(NULL));
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		unset(cmd->msg);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		write(1, "exit 😱 😭", 15);
		return (-1);
	}
	else
		ret = exec(cmd);
	return (ret);
}
