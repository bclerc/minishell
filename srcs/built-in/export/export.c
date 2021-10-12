/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/12 10:50:34 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"
/**               
 *  A METTRE DANS LE MAIN ET DANS LE .h
 **/


int	copy_env(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->export = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
	{
		env->export[i] = ft_strdup(envp[i]);
		i++;
	}
	env->export[i] = 0;
	return (1);
}
/**
 *  FIN MAIN
 */

int	export(char **envp, char *path)
{
	char	**env;
	int		fd;
	int		i;

	i = 0;
	fd = get_fd(path);
	env = envp;
	export_sort(env, get_env_lenght(env));
	while (env[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
	free_env(env);
}
