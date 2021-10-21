/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:15:37 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/21 11:16:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int execute_bin_commands(char **argv)
{
	int		ret;
	int		status;
	pid_t	pid;
	pid_t	child;
	char	**cmd;
	char	*find;
	char	*tmp;

	core.child = fork();
	core.child_exist = 1;
	if (core.child == 0)
	{
		cmd = argv;
		tmp = ft_strdup("/bin/");
		find = ft_strjoin(tmp, argv[0]);
		free(tmp);
		ret = execve (find, cmd, 0);
		if (ret < 0)
			printf("%s: command not found\n", argv[0]);
		free(find);
		exit(-1);
	}
	else{
		 status;
    	waitpid(core.child, &status, 0);
		core.child_exist = 0;
	}
}

int	execute_commands(char *args, char **envp, char *path)
{
	char	**argv;
	char	*cmd;
	int		ret;

	argv = ft_strsplit(args, ' ');
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
	{
		printf("\nGood Bye\n");
		core.status = -1;
		return (-1);
	}
	if (ret == 1)											// a refaire
		return (ret);
	execute_bin_commands(argv);
	rm_split(argv);
	return (1);
}