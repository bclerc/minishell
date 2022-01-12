/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/12 12:40:52 by bclerc           ###   ########.fr       */
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
	t_cmd	*tmp;
	t_cmd	*cmd;
	char	*str;
	char	*rd;
	char	*prompt;
	int		status;

	status = 0;
	while (status != -1)
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
				status = -1;
			continue ;
		}
		str = ft_strdup(rd);
		if (!str)
		{
			free(rd);
			break ;
		}
		free(rd);
		add_history(str);
		rd = transform_str(str, status);
    	cmd = ft_launch_parser(rd, &cmd);
		free(rd);
		if (!cmd)
			exit(0); // fct exit avec free
    	cmd = ft_redir(cmd);
		if (!cmd)
			exit(0); // fct exit avec free
		tmp = dupp_cmd(cmd);
		status = m_pipe(tmp);
		m_exit(tmp, M_EXIT_FORK, NULL);
	}
	del_env();
	free(core);
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
	core->parent = getpid();
	minishell();
	return (0);
}
