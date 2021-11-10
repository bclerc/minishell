/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/11/10 17:22:07 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_core core;

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

void	minishell(int ac, char **av, char **envp)
{
	char	*str;
	char	*prompt;
	t_cmd	*cmd;
	t_redir	*redir;

	redir = NULL;
	while (core.status)
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
		cmd = ft_launch_parser(str, envp, &cmd);
		// inserer la liste redir dans cmd si < > << >> :
		//cmd = ft_redir(cmd);
		//printf("cmd : nb = %d cmd = %s, spec = %s, msg = %s, std = %d fd = %s\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, cmd->fd);
		// if (execute_commands(str, envp, 0) == -1)
		// {
		// 	free(prompt);
		// 	free(str);
		// 	break ;
		// }
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
	core.child_exist = 0;
	env = NULL;
	i = 0;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	while (envp[i])
		i++;
	sa = init_signal();
	//sigaction(SIGINT, &sa, NULL);
	core.status = 1;
	core.parent = getpid();
	minishell(ac, av, envp);
	return (0);
}