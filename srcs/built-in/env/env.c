/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/11 15:41:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	export(char **envp, char *path)
{
	char **env;
	int		fd;
	int		i;

	i = 0;
	fd = get_fd(path);
	env = envp;
	while (env[i])
	{
		write(fd, env[i], ft_strlen(env[i]));
		write(fd, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	export(envp, argv[1]);
}
