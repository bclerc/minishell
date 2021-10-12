/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:15:09 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 14:39:19 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

// TODO:
//	Foncionne quand la variable possede les memes lettres que le debut d'une variable dans l'env
// 	Ex: LS retourn LSCOLOR,
//je sais le regler mais la j'ai la flemme donc je vais le faire plus tard

char *get_env_variable(char *var, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
