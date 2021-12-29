/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:15:09 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/29 13:03:16 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**env_to_char(void)
{
	char	**char_env;
	t_env	*env;
	int		count;
	int		i;

	count = 0;
	env = core->env;
	while (env->next)
	{
		count++;
		env = env->next;
	}
	char_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!char_env)
		return (NULL);
	env = core->env;
	i = 0;
	while (i < count)
	{
		char_env[i] = ft_strdup(env->value);
		env = env->next;
		i++;
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
	if (!core->env)
		core->env = tmp;
	else
	{
		env = core->env;
		while (env->next != NULL)
		{
			env = env->next;
			i++;
		}
		env->next = tmp;
	}
	return (1);
}

int	del_env_variable(char *var)
{
	t_env	*tmp;
	t_env	*last;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen(var)) == 0)
		{
			if (last)
				last->next = tmp->next;
			else if (tmp->next)
				core->env = NULL;
			else
				core->env = tmp;
			ft_bzero(tmp->value, ft_strlen(tmp->value));
			free(tmp->value);
			free(tmp);
			return (1);
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (1);
}

char	*get_env_variable(char *var)
{
	t_env	*tmp;
	int		i;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen(var)) == 0)
		{
			i = 0;
			while (tmp->value[i] != '=')
				i++;
			return (tmp->value + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
