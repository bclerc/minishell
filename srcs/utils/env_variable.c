/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:15:09 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 13:38:23 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	rebuild_env(t_env *tmp, t_env *last)
{
	if (last && tmp->next)
		last->next = tmp->next;
	else if (!last && tmp->next)
		g_core->env = tmp->next;
	else if (last && !tmp->next)
		last->next = NULL;
	else
		g_core->env = NULL;
}

int	del_env_variable(char *var)
{
	t_env	*tmp;
	t_env	*last;

	tmp = g_core->env;
	last = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen(var)) == 0)
		{
			rebuild_env(tmp, last);
			free(tmp->value);
			tmp->next = NULL;
			free(tmp);
			return (1);
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (1);
}

char	*get_env_variable_str(char *var)
{
	t_env	*tmp;
	int		len;
	int		i;

	tmp = g_core->env;
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

char	*get_env_variable(char *var)
{
	t_env	*tmp;
	int		i;

	tmp = g_core->env;
	if (!tmp)
		return (NULL);
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
	return ("  ");
}
