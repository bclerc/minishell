/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/11/16 17:05:13 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core core;

char **duplicate_env(char **envp)
{
	int i;
	char **tmp;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * i);
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (tmp);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
		if (signum == SIGINT)
		{
			if (core.child_exist)
			{
				if (core.child == 0)
					exit(-1);
			}
			else
			{
				printf("\n");
				rl_on_new_line();
        		rl_replace_line("", 0);
        		rl_redisplay();
			}
		}
}

void	minishell(int ac, char **av)
{
	char	*str;
	char	*prompt;
	t_cmd	cmd;


	char **envp = core.envp;
	while (core.status != -1)
	{
		prompt = get_promps(envp);
		str = readline(prompt);
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue;
		}
		add_history(str);
		str = transform_str(str, core.envp);
		cmd = ft_launch_parser(str, envp);
		if (execute_commands(&cmd) == -1)
		{
			printf("Good bye\n");
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
	char	**env;
	struct sigaction	sa;

	(void)av;
	core.child_exist = 0;
	core.envp = duplicate_env(envp);
	i = 0;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	while (envp[i])
		i++;
	sa = init_signal();
	sigaction(SIGINT, &sa, NULL);
	core.status = 1;
	core.parent = getpid();
	minishell(ac, av);
	return (0);
}