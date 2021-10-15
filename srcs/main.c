/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/10/15 09:53:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core core;


void	signal_handler(int signum, siginfo_t *info, void *context)
{
		if (signum == SIGINT)
		{
			if (core.main_child == 0)
			{
				close(core.fd[0]);
				write(core.fd[1], "1", 2);
				exit(-1);
			}
		}
}

void	minishell(int ac, char **av, char **envp)
{
	char	*str;

	while (42)
	{
		str = readline(get_promps(envp));
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue;
		}
		add_history(str);
		if (execute_commands(str, envp, 0) == -1)
			break ;
		parser(str, envp);
	}
	
}

struct sigaction	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	return (sa);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*str;
	char	readbuffer[3];
	t_list	*env;
	struct sigaction	sa;
	(void)av;
	env = NULL;
	i = 0;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	while (envp[i])
		i++;
	env = ft_get_env(env, envp);
	sa = init_signal();
	sigaction(SIGINT, &sa, NULL);
	core.status = 1;
	core.main_parent = getpid();
	while (core.status != -1)
	{
		pipe(core.fd);
		core.main_child = fork();
		if (core.main_child == 0)
		{
			minishell(ac, av, envp);
			close(core.fd[0]);
			write(core.fd[1], ft_itoa(core.status), 3);
			exit(0);
		}
		else
		{
			int status;
			waitpid(core.status, &status, 0);
			close(core.fd[1]);
			read(core.fd[0], readbuffer, sizeof(readbuffer));
			core.status = atoi(readbuffer);
		}
		str = readline(get_promps(envp));
		add_history(str);
		//execute_commands(str, envp, 0);
		parser(str, envp);
		//parser(str, envp);
	}
	return (0);
}

t_list	*ft_get_env(t_list *env, char **envp)
{
	int		i;
	t_list	*new;
	char	*str;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		if (!str)
			return (NULL); // faire une fct exit
		new = ft_lstnew(str);
		ft_lstadd_back(&env, new);
		// faire une fct exit ici aussi en cas de souci?
		i++;
	}
	return (env);
}