/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:41:31 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 14:59:26 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//	TODO:
//	Leak mdr 

char *get_current_dir_name(char **envp)
{
	char	*dir;
	char	**tmp;
	int		i;

	tmp = ft_split(get_env_variable("PWD", envp), '/');
	i = 0;
	while (tmp[i])
		i++;
	dir = ft_strdup(tmp[i - 1]);
	free(tmp);
	return (dir);
}

char *get_promps(char **envp)
{
	char *prompts;

	prompts = ft_strdup("\e[1;35mMinishell \e[1;36m(\e[1;34m");
	prompts = ft_strjoin(prompts, get_current_dir_name(envp));
	prompts = ft_strjoin(prompts, ft_strdup("\e[1;36m) \e[1;35m$ \e[1;37m"));
	return (prompts);
}