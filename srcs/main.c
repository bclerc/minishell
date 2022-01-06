/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/06 14:05:32 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core *core;

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		if (core->child_exist)
			return ;
		return ;
	}
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
	char	*rd;
	char	*prompt;
	t_cmd	*cmd;
	t_cmd	*tmp;

	while (core->status != 0)
	{
		prompt = get_promps();
		rd = readline(prompt);
		free(prompt);
		if (!rd)
			break ;
		if (!rd || ft_strlen(rd) == 0)
		{
			printf("\n");
			if (!rd)
				core->status = 0;
			continue ;
		}
		str = ft_strdup(rd);
		free(rd);
		add_history(str);
		str = transform_str(str);
    	cmd = ft_launch_parser(str, &cmd);
		free(str);
		if (!cmd)
			exit(0);
    	cmd = ft_redir(cmd);
		cmd = dup_cmd(cmd);
		m_pipe(cmd);
		m_exit(cmd, M_EXIT_FORK, NULL);
	}
	//m_exit(cmd, M_EXIT_SUCCESS, NULL);
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
	get_env(envp);
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	core->status = 1;
	core->parent = getpid();
	minishell();
	return (0);
}
