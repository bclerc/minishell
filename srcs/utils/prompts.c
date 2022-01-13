/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:41:31 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/13 12:37:40 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_current_dir_name(void)
{
	char	*dir;
	char	**tmps;
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	if (ft_strlen(pwd) == 1)
	{
		free(pwd);
		return (ft_strdup("/"));
	}
	tmps = ft_strsplit(pwd, '/');
	free(pwd);
	i = 0;
	while (tmps[i])
		i++;
	if (i == 1)
		dir = ft_strdup(tmps[0]);
	else
		dir = ft_strdup(tmps[i - 1]);
	rm_split(tmps);
	return (dir);
}

char	*get_promps(void)
{
	char	*prompts;
	char	*tmp;
	char	*tmp2;
	char	*pwd;

	pwd = get_current_dir_name();
	tmp = ft_strdup("\e[1;36m(\e[1;34m");
	tmp2 = ft_strjoin(tmp, pwd);
	free(pwd);
	free(tmp);
	tmp = ft_strdup("\e[1;36m) \e[1;35m🚬 \e[0;37m");
	prompts = ft_strjoin(tmp2, tmp);
	free(tmp2);
	free(tmp);
	return (prompts);
}
