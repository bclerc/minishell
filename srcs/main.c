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

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*str;
	t_list	env;

	(void)av;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	i = 0;
	while (envp[i])
		i++;
	// i = -1;
	// while (envp[++i])
	// 	printf("envp[%i] = %s\n", i, envp[i]);
	// if (!env)
	// 	return (1);
	ft_get_env(&env, envp);
	while (42)
	{
		str = readline("minishell42> ");
		if (!str)
			return (1);
	}
	return (0);
}

t_list	*ft_get_env(t_list *env, char **envp)
{
	int		i;
	t_list	*new;
	char	*str;

	i = 0;
	while (envp[i])
	{
		printf("envp[%i] = %s\n", i, envp[i]);
		str = ft_strdup(envp[i]);
		if (!str)
			return (NULL); // faire un exit
		new = ft_lstnew(str);
		ft_lstadd_back(&env, new);
		printf("env.content = %s\n", env->content);
		i++;
	}
	return (env);
}