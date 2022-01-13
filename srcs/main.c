/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:41:06 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/13 16:21:45by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core	*g_core;

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_core->child_exist)
			return ;
		return ;
	}
	if (signum == SIGINT)
	{
		if (g_core->child_exist)
		{
			if (g_core->child == 0)
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

int	start(t_cmd *cmd, char *str)
{
	t_cmd	*tmp;
	int		status;

	if (!cmd)
		return (-2);
	cmd = ft_redir(cmd);
	if (!cmd)
		return (-2);
	status = 0;
	tmp = dupp_cmd(cmd);
	status = m_pipe(tmp);
	m_exit(tmp, M_EXIT_FORK, NULL);
	return (status);
}

char	*start_prompt(void)
{
	char	*prompt;
	char	*ret;

	prompt = get_promps();
	ret = readline(prompt);
	free(prompt);
	return (ret);
}

void	minishell(char *rd, int status)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (status != -1)
	{
		rd = start_prompt();
		if (!rd)
			break ;
		if (!rd || ft_strlen(rd) == 0)
		{
			printf("\n");
			if (!rd)
				status = -1;
			continue ;
		}
		add_history(rd);
		rd = transform_str(rd, status);
		cmd = ft_launch_parser(rd, (t_cmd *[1]){(&(t_cmd){})});
		status = start(cmd, rd);
		free(rd);
	}
	write(1, "\n", 1);
	del_env();
	free(g_core);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char	*rd;
	int		status;

	(void)av;
	g_core = (t_core *)malloc(sizeof(*g_core));
	if (!g_core)
		return (0);
	g_core->child_exist = 0;
	g_core->env = NULL;
	get_env(envp);
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	g_core->parent = getpid();
	minishell(rd, status);
	return (0);
}
