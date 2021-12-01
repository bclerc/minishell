/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:05:05 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/01 13:53:48 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	change_env(char	**new_env)
{
	int		i;
	int 	total;
	
	total = 0;
	i = get_env_length(core->envp);
	while (i >= 0)
	{

		if (core->envp[i] != NULL)
		{
			free(core->envp[i]);
			core->envp[i] = NULL;
		}
		total++;
		i--;
	}
	printf("%d was been freed\n", total);
	getchar();
	free(core->envp);
	core->envp = 0;
	core->envp = new_env;
}


int	get_env_length(char **env)
{
	int i;

	if (!env)
		return (0);
	i = -1;
	while (env[++i]);
	return (i);
}

void	free_env(char **env)
{
	int i;

	i = get_env_length(env);
	while (i >= 0)
	{
		free(env[i]);
		i--;
	}
	free(env);
}

void	export_sort(char **value, int len)
{
	char	*tmp;
	int		i;

	tmp = 0;
	i = 0;
	i = 0;
	while (i < len - 1)
	{
		if (value[i][0] <= value[i + 1][0])
			i++;
		else
		{
			tmp = value[i];
			value[i] = value[i + 1];
			value[i + 1] = tmp;
			i = 0;
		}
	}
}

char **re_alloc(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i + 2);
	if (!new_env)
		exit(1);	
	return (new_env);
}
