/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:15:09 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/02 12:39:14 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// TODO:
//	Foncionne quand la variable possede les memes lettres que le debut d'une variable dans l'env
// 	Ex: LS retourn LSCOLOR,
//je sais le regler mais la j'ai la flemme donc je vais le faire plus tard


int	getEnv(char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (envp[i])
	{
		add_env_variable(envp[i]);
		i++;
	}
	return (1);
}

int	add_env_variable(char *var)
{
	t_env *tmp;
	t_env *env;
	int i = 0;

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
	t_env *tmp;
	t_env *last;
	t_env *swp;

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

char *get_env_variable(char *var)
{
	t_env *tmp;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen(var)) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
}

