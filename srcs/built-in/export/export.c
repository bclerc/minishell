/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:14:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/11 15:39:16 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**               
 *  A METTRE DANS LE MAIN ET DANS LE .h
 **/


typedef struct s_env
{
	char **env;
	char **export;
} 				t_env;
void	export_sort(char **value, int len);
int		get_env_lenght(char **env);
int get_fd(char *path);
int ft_strlen(char *str);
int add_env_variable(t_env *env, char *var);
char *ft_strdup(const char *str);


int copy_env(char **envp, t_env *env)
{
	int i;

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
	char **env;
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
}

int main(int argc, char **argv, char **envp)
{
	t_env env;
	
	copy_env(envp, &env);
	if (argc == 2)
	{
		add_env_variable(&env, argv[1]);
		export(env.export, 0);
	}
	else
		export(env.export, argv[1]);
	free_env(env.export);
}


