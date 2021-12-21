/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/21 15:46:13 by asgaulti         ###   ########.fr       */
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

void	minishell(void)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;

	while (core->status != 0)
	{
		prompt = get_promps();
		str = ft_strdup(readline(prompt));
		free(prompt);
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue ;
		}
		add_history(str);
		str = transform_str(str);
    	cmd = ft_launch_parser(str, &cmd);
		if (!cmd)
			exit(0); // le temps de regler m_exit pour eviter les segfaults qui puent
			//m_exit(cmd, M_EXIT_MALLOC_ERROR, NULL); // a modifier
		//cmd = ft_check_spec(&cmd);
    	cmd = ft_redir(cmd);
	puts("che");
		m_pipe(cmd);
		m_exit(cmd, M_EXIT_FORK, NULL);
	}
	m_exit(cmd, M_EXIT_SUCCESS, NULL);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
		return (0);
	core->child_exist = 0;
	core->env = NULL;
	getEnv(envp);
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	//signal(SIGINT, signal_handler);
	core->status = 1;
	core->parent = getpid();
	minishell();
	return (0);
}
