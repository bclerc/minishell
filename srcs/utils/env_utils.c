/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:03:46 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 13:03:35 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
int	fill_env(void)
{
	char *var;
	char *tmp;

	tmp = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", tmp);
	add_env_variable(var);
	free(var);
	var = ft_strjoin("OLDPWD=", tmp);
	add_env_variable(var);
	free(var);
	var = ft_strjoin("HOME=", tmp);
	add_env_variable(var);
	free(var);
	free(tmp);
	add_env_variable("PATH=/bin/");
}

int	get_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_env_variable(envp[i]);
		i++;
	}
	return (1);
}

int	get_env_count(void)
{
	t_env	*env;
	int		count;

	env = g_core->env;
	count = 0;
	while (env->next)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_char(void)
{
	char	**char_env;
	t_env	*env;
	int		count;
	int		i;

	if (!g_core->env)
		add_env_variable(getcwd(0, 0));
	env = g_core->env;
	count = get_env_count();
	char_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!char_env)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		char_env[i] = ft_strdup(env->value);
		env = env->next;
	}
	char_env[i] = NULL;
	return (char_env);
}

int	add_env_variable(char *var)
{
	t_env	*tmp;
	t_env	*env;
	int		i;

	i = 0;
	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->value = ft_strdup(var);
	tmp->next = NULL;
	if (!g_core->env)
		g_core->env = tmp;
	else
	{
		env = g_core->env;
		while (env->next != NULL)
		{
			env = env->next;
			i++;
		}
		env->next = tmp;
	}
	return (1);
}
