/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:41:31 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/18 12:53:49 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char *get_current_dir_name(char **envp)
{
	char	*dir;
	char	**tmps;
	char	*pwd;
	int		i;

	pwd = get_env_variable("PWD", envp);
	tmps = ft_strsplit(pwd, '/');
	free(pwd);
	i = 0;
	while (tmps[i])
		i++;
	if (i == 1)
		dir = ft_strdup("/");
	else
		dir = ft_strdup(tmps[i - 1]);
	rm_split(tmps);
	return (dir);
}

char *get_promps(char **envp)
{
	char *prompts;
	char *tmp;
	char *tmp2;
	char *pwd;

	pwd = get_current_dir_name(envp);
	tmp = ft_strdup("\e[1;35mMinishell \e[1;36m(\e[1;34m");
	tmp2 = ft_strjoin(tmp, pwd);
	free(pwd);
	free(tmp);
	tmp = ft_strdup("\e[1;36m) \e[1;35m$ \e[0;37m");
	prompts = ft_strjoin(tmp2, tmp);
	free(tmp2);
	free(tmp);
	return (prompts);
}