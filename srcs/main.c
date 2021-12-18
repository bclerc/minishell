/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/18 17:59:05 by bclerc           ###   ########.fr       */
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
		if (!str || ft_strlen(str) == 0)
		{
			printf("\n");
			continue;
		}
		add_history(str);
    	cmd = ft_launch_parser(str, &cmd);
		printf("cmd : nb = %d cmd = %s, spec = %s, msg = %s, std = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std);
		//cmd = ft_check_spec(&cmd);
    	cmd = ft_redir(cmd);
		m_pipe(cmd);
		free(prompt);
		free(str);
	}
	m_exit(cmd, M_EXIT_MALLOC_ERROR, "minishell (main.c)");
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
