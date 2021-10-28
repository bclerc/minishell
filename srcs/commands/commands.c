/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/28 11:38:25 by bclerc           ###   ########.fr       */
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
	
	if (cmd->msg == NULL)
	{
		argv = malloc(sizeof(char *) * 1);
		argv[0] = ft_strdup(cmd->cmd);
		return (argv);
	}
	i = 0;		
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
	return (argv);
}
int execute_bin_commands(t_cmd *cmd)
{
	int		ret;
	int		status;
	pid_t	pid;
	pid_t	child;
	char	*find;
	char	*tmp;
	char	**argv;

	core.child = fork();
	core.child_exist = 1;
	if (core.child == 0)
	{
		tmp = ft_strdup("/bin/");
		find = ft_strjoin(tmp, cmd->cmd);
		free(tmp);

		argv = create_execve_argv(cmd);
	int		i = 0;
	while (argv[i])
	{
		printf("ARGV %d : %s\n", i, argv[i]);
		i++;
	}
		ret = execve (find, argv, 0);
		if (ret < 0)
			printf("%s: command not found\n", cmd->cmd);
		free(find);
		exit(-1);
	}
	else{
		 status;
    	waitpid(core.child, &status, 0);
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
	execute_bin_commands(cmd);
	return (1);
}