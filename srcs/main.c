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
	t_list	*env;

	(void)av;
	env = NULL;
	i = 0;
	if (ac != 1)
		return (ft_print("There are too many arguments!\n", 1));
	while (envp[i])
		i++;
	env = ft_get_env(env, envp);
	// while (env->next)
	// {
	// 	printf("content = %s\n", env->content);
	// 	env = env->next;
	// }
	while (42)
	{
		str = readline("minishell42> ");
		if (!str)
			return (1);
		ft_get_cmd(str);
	}
	return (0);
}

t_list	*ft_get_env(t_list *env, char **envp)
{
	int		i;
	t_list	*new;
	char	*str;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		if (!str)
			return (NULL); // faire une fct exit
		new = ft_lstnew(str);
		ft_lstadd_back(&env, new);
		// faire une fct exit ici aussi en cas de souci?
		i++;
	}
	return (env);
}