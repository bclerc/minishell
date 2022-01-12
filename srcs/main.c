/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/12 18:58:12 by asgaulti         ###   ########.fr       */
=======
/*   Updated: 2022/01/12 18:47:10 by bclerc           ###   ########.fr       */
>>>>>>> c74489f9bc24329db4d1759ae3098f756c98ed78
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core	*g_core;

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{	
		
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
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	start(char *str)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		status;

	cmd = ft_launch_parser(str, &cmd);
	if (!cmd)
		exit(0);
	cmd = ft_redir(cmd);
	if (!cmd)
		exit(0);
	tmp = dupp_cmd(cmd);
	status = m_pipe(tmp);
	free(str);
	m_exit(tmp, M_EXIT_FORK, NULL);
	return (status);
}

void	minishell(void)
{
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
		add_history(rd);
		status = start(transform_str(rd, status));
	}
	del_env();
	free(g_core);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	g_core = (t_core *)malloc(sizeof(t_core));
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
	minishell();
	return (0);
}
