/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:32 by asgaulti          #+#    #+#             */
/*   Updated: 2021/10/07 16:51:22 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*str;
	t_env	env;

	(void)av;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	i = 0;
	while (envp[i])
		i++;
	env.env = malloc(sizeof(char *) * i + 1);
	if (!env.env)
		return (1);
	// i = 0;
	// while (envp[i])
	// {
	// 	env.env[i] = ft_strdup(envp[i]);
	// 	printf("envp[%i] = %s\n", i, envp[i]);
	// 	printf("env.env[%i] = %s\n", i, env.env[i]);
	// 	i++;
	// }
	while (42)
	{
		str = readline("minishell42> ");
		if (!str)
			return (1);
	}
	return (0);
}
