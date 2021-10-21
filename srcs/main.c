/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/10/21 10:25:08 by astrid           ###   ########.fr       */
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
	char	*prompt;

	while (42)
	{

		prompt = get_promps(envp);
		str = readline(prompt);
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue;
		}
		add_history(str);
		str = transform_str(str, envp);
		parser(str, envp);
		if (execute_commands(str, envp, 0) == -1)
		{
		free(prompt);
			free(str);
			break ;
		}
		free(prompt);	
		free(str);
	}
}

struct sigaction	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
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
	sa = init_signal();
	//sigaction(SIGINT, &sa, NULL);
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
		printf("\n");
	}
	return (0);
}