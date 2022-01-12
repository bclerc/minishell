/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:15:09 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 17:05:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	del_env_variable(char *var)
{
	t_env	*tmp;
	t_env	*last;

	tmp = g_core->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen(var)) == 0)
		{
			if (last)
				last->next = tmp->next;
			else if (tmp->next)
				g_core->env = NULL;
			else
				g_core->env = tmp;
			ft_bzero(tmp->value, ft_strlen(tmp->value));
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			tmp = NULL;
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
	return (var);
}
