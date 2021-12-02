/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/02 13:58:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core *core;

void	signal_handler(int signum)
{
		if (signum == SIGINT)
		{
			if (core->child_exist)
			{
				if (core->child == 0)
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

	while (core->status != -1)
	{
		prompt = get_promps(core->envp);
		str = readline(prompt);
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue;
		}
		add_history(str);
		//str = transform_str(str, core->envp);
		cmd = ft_launch_parser(str, NULL);
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

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	readbuffer[3];
	char	**env;

	(void)av;
	core = (t_env *)malloc(sizeof(t_core));
	if (!core)
		return (0);
	core->child_exist = 0;
	core->env = NULL;
	getEnv(envp);
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	signal(SIGINT, signal_handler);
	core->status = 1;
	core->parent = getpid();
	minishell(ac, av);
	return (0);
}