/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:26 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/22 12:06:44 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void	unset(char **env, char *var)
{
	char	**ret;
	char	**tmp;
	int		i;

	ret = (char **)malloc(sizeof(ret) * get_env_lenght(env));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)))
			i++;
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	rm_split(env);
	env = ret;
}