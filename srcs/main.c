/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/14 17:26:08 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core	*g_core;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_core->child_exist)
		{
			if (g_core->child == 0)
				kill(g_core->child, 9);
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			//rl_replace_line("", 0);
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
	status = m_pipe(tmp, status);
	m_exit(tmp, M_EXIT_FORK, NULL);
	return (status);
}

void	quit_minishell(int status)
{
	printf("\nBye\n");
	del_env();
	free(g_core);
	exit(status);
}

void	minishell(char *rd, int status)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (status > -1)
	{
		rd = start_prompt();
		if (!rd)
			break ;
		if (!rd || ft_strlen(rd) == 0)
		{
			if (!rd)
				status = -1;
			continue ;
		}
		add_history(rd);
		rd = transform_str(rd, status);
		if (!rd)
			continue ;
		cmd = ft_launch_parser(rd, (t_cmd *[1]){(&(t_cmd){})});
		status = start(cmd, rd);
		free(rd);
	}
	quit_minishell(status + 300);
}

int	main(int ac, char **av, char **envp)
{
	char	*rd;
	int		status;

	(void)av;
	status = 0;
	g_core = (t_core *)malloc(sizeof(*g_core));
	if (!g_core)
		return (0);
	g_core->child_exist = 0;
	g_core->env = NULL;
	get_env(envp);
	if (!g_core->env)
		fill_env();
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	g_core->parent = getpid();
	minishell(rd, status);
	return (0);
}
