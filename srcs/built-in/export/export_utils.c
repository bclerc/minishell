/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:05:05 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 11:38:13 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_env_lenght(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int i;

	i = get_env_lenght(env);
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

int add_env_variable(t_env *env, char *var)
{
	char	**new_env;
	int		i;	
	int		placed;
	
	new_env = re_alloc(env->export);
	if (!new_env)
		return (0);
	i = 0;
	placed = 0;
	while (env->export[i])
	{
		new_env[i] = ft_strdup(env->export[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (0);
	new_env[i + 1] = 0;
	env->export = new_env;
	return (1);
}