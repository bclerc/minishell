/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/18 17:56:29 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **get_argv(t_cmd *cmd)
{
	char	**ret;
	char	**tmp;
	int		i;

	if (cmd->msg)
	{
		tmp = ft_strsplit(cmd->msg, ' ');
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i])
			i++;
		ret = (char **)malloc(sizeof(char *) * (i + 2));
		ret[0] = cmd->cmd;
		i = 0;
		while (tmp[i])
		{
			ret[i + 1] = ft_strdup(tmp[i]);
			i++;
		}
		ret[i + 1] = NULL;
		rm_split(tmp);
		return (ret);
	}
	ret = (char **)malloc(sizeof(char *) * 2);
	ret[0] = cmd->cmd;
	ret[1] = NULL;
	return (ret);	
}

char **get_splited_path(void)
{
	char	*tmp;
	char	**ret;

	tmp = get_env_variable("PATH");
	if (!tmp)
		return (NULL);
	ret = ft_strsplit(tmp, ':');
	return (ret);
}

char *get_path(char *path, char *cmd)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	
	return (ret);
}

int exec(t_cmd *cmd)
{
	char	**path;
	char	**argv;
	char	**tab_env;
	int		status;
	int		i;

	status = 0;
	path = get_splited_path();
	if (!path)
	{
		printf("Execution path not found\n");
		return (-1);
	}
	i = -1;
	core->child_exist = 1;
	argv = get_argv(cmd);
	tab_env = env_to_char();
	while (path[++i] && status == 0)
	{
		if (execve(get_path(path[i], cmd->cmd), argv,
			tab_env) > -1)
			status = 1;
	}
	if (status == 0)
	{
		if (execve(cmd->cmd, argv, tab_env) > -1)
			status = 1;
		else
			printf("%s: command not found\n", cmd->cmd);
	}
	rm_split(argv);
	rm_split(tab_env);
	core->child_exist = 0;
	return (1);
}

int	execute_commands(t_cmd *cmd)
{
	int		ret;
	
	ret = 0;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ret = (cd(cmd->msg));
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ret = (echo(cmd->msg, 0, 0));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ret = (env(NULL));
	if (ft_strcmp(cmd->cmd,	"export") == 0)
		ret = (export(NULL, cmd->msg));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ret = (pwd(cmd->msg));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		ret = unset(cmd->msg);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		core->status = 0;
		return (-1);
	}
	if (ret == 1 || ret == -1)
		return (ret);
	exec(cmd);
	return (1);
}