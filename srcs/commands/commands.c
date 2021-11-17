/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/11/17 15:23:26 by bclerc           ###   ########.fr       */
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
int execute_bin_commands(t_cmd *cmd)
{
	int fd[2];
	char **argv;
	char **path;
	char *exec_path;
	int i;
	int executed;
	char foo[4000];

	pipe(fd);
	core.child = fork();
	core.child_exist = 1;
	executed = 0;
	path = ft_strsplit(get_env_variable("PATH", core.envp), ':');
	if (core.child == 0)
	{
		//dup2 (fd[1], 1);
    	//close(fd[0]);
    	//close(fd[1]);
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
		{
			if (execve(cmd->cmd, create_execve_argv(cmd), NULL) > -1)
				executed = 1;
			else
				printf("%s: command not found\n", cmd->cmd);
		}
		rm_split(path);
		exit(1);
	}
	else
	{
		// close(fd[1]);
    	// int nbytes = read(fd[0], foo, sizeof(foo));
    	// printf("Output: (%.*s)\n", nbytes, foo);
    	 waitpid(core.child, NULL, 0);
		 core.child_exist = 0;
	}
}

int	execute_commands(t_cmd *cmd)
{
	char	**argv;
	int		ret;
	
	ret = 0;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ret = (cd(core.envp, cmd->msg));
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
	printf("ret for cmd %s is %d\n", cmd->cmd, ret);
	if (ret == 1)											// a refaire
		return (ret);
	if (ret == -1)
		return (-1);
	execute_bin_commands(cmd);
	return (1);
}