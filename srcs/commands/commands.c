/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/08 13:37:36 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//
//
//	SUPER SALE COMME FONCTION JE BOSSE DESSUS
//	DESO POUR LES YEUX A L'AVANCE
//
//

char **create_execve_argv(t_cmd *cmd) 
{
	int i;
	int count;
	char **argv;
	char **tmp;
	char *empty[] = {" ", NULL};

	if (!cmd->msg)
		return (empty);		
	while (cmd->msg[i])
	{
		if (cmd->msg[i] == ' ')
			count++;
		i++;
	}	
	argv = malloc(sizeof(char *) * i + 2);
	argv[0] = ft_strdup(cmd->cmd);

	tmp = ft_strsplit(cmd->msg, ' ');
	i = 0;
	while (tmp[i])
	{
		argv[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	argv[i] = NULL;  
	return (argv);
}
int execute_bin_commands(t_cmd *cmd, char **envp)
{
	char **argv;
	char **path;
	char *exec_path;
	int i;
	int executed;

	core.child = fork();
	core.child_exist = 1;
	executed = 0;
	path = ft_strsplit(get_env_variable("PATH", envp), ':');
	if (core.child == 0)
	{
		i = 0;
		while (path[i])
		{
			exec_path = ft_strjoin(path[i], "/");
			exec_path = ft_strjoin(exec_path, cmd->cmd);
			if (execve(exec_path, create_execve_argv(cmd), NULL) > -1)
			{
				executed = 1;
				free(exec_path);
				break ;
			}
			i++;
			free(exec_path);
		}
		if (executed == 0)
			printf("%s: command not found\n", cmd->cmd);
		rm_split(path);
		exit(-1);
	}
	else
	{
    	waitpid(core.child, NULL, 0);
		core.child_exist = 0;
	}
}

int	execute_commands(t_cmd *cmd, char **envp)
{
	char	**argv;
	int		ret;
	
	ret = 0;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ret = (cd(envp, cmd->msg));
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ret = (echo(cmd->msg, cmd->std , 0));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		ret = (env(envp, cmd->std));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		ret = (export(envp, cmd->std, NULL));
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
	if (ret == 1)											// a refaire
		return (ret);
	execute_bin_commands(cmd, envp);
	return (1);
}