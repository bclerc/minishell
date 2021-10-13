/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/13 11:16:00 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_bin_commands(char **argv)
{
	pid_t	pid;
	pid_t	child;
	char	**cmd;
	char	*find;

	pid = getpid();
	child = fork();

	if (child == 0)
	{
		cmd = argv;
		find = ft_strdup("/bin/");
		find = ft_strjoin(find, argv[0]);
		execve (find, cmd, 0);
	}
	else{
		    int status;
    	waitpid(child, &status, 0);
	}
}

int	execute_commands(char *args, char **envp, char *path)
{
	char	**argv;
	char	*cmd;
	int		ret;

	argv = ft_split(args, ' ');
	cmd = argv[0];
	ret = 0;
	if (ft_strcmp(cmd, "cd") == 0)
		ret = (cd(envp, argv[1]));
	if (ft_strcmp(cmd, "echo") == 0)
		ret = (echo(argv[1], path, 0));
	if (ft_strcmp(cmd, "env") == 0)
		ret = (env(envp, path));
	if (ft_strcmp(cmd, "export") == 0)
		ret = (export(envp, path));
	if (ft_strcmp(cmd, "pwd") == 0)
		ret = (pwd(path));
	if (ft_strcmp(cmd, "unset") == 0)
		ret = (1);											//pas fait
	if (ft_strcmp(cmd, "exit") == 0)
		exit(1);
	if (ret == 1)											// a refaire
		return (ret);
	execute_bin_commands(argv);
	return (1);
}