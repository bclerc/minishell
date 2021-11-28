/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/28 18:23:37 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **get_argv(t_cmd *cmd)
{
	char *tab[2] = {" ", NULL};
	char **ret;
	int i;

	if (cmd->msg)
	{	
		//VOIR AVEC ASTRID		
		return (ft_strsplit(cmd->msg, ' '));
	}
	return (tab);
}

char **get_path(char *path, char *cmd)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	printf("TMP: %s\n", tmp);
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

int exec(t_cmd *cmd)
{
	int status;
	int i;
	char **path;

	status = 0;
	path = ft_strsplit(get_env_variable("PATH", core.envp), ':');
	i = 0;
	core.child = fork();
	if (core.child == 0)
	{
		while (path[i] && status == 0)
		{
			printf("Path: %s\n", get_path(path[i], cmd->cmd));
			printf("CMD: %s\n", get_argv(cmd)[0]);
			if (execve(get_path(path[i], cmd->cmd), get_argv(cmd),
				core.envp) > -1)
				status = 1;				
			perror("trouducul: ");
			i++;
		}
	}
	else
		waitpid(core.child, NULL, 0);	
}

int	execute_commands(t_cmd *cmd)
{
	char	**argv;
	int		ret;
	
	ret = 0;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ret = (cd(cmd->msg));
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ret = (echo(cmd->msg, cmd->std , 0));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ret = (env(core.envp, cmd->std));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		ret = (export(cmd->std, cmd->msg));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ret = (pwd(cmd->msg));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		ret = (1);											//pas fait
	if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		printf("\nGood Bye\n");
		core.status = -1;
		return (-1);
	}
	if (ret == 1 || ret == -1)											// a refaire
		return (ret);
	exec(cmd);
	return (1);
}