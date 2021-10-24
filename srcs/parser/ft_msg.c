/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:10:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/24 13:41:04 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg(t_arg *arg, char **cpy, int i, int j, t_cmd *cmd)
{
	char	*tmp;
    int     c;
	int		start;
    
	//printf("cpy[%d] = %s\n", i, cpy[i]);
	// if (!cpy[i])
	// 	return (ft_print("\n", -1));
	//cpy[i] = ft_parse_msg(cmd, cpy, i);
	if (j == cmd->cpy_nb - 1)
		cmd->msg = ft_strdup(cpy[j]);
	else
	{
		if (j == 1)
		{
			c = ft_which_cmd(cpy);
			start = 5;
            if (c == 1)
                tmp = ft_echo_msg(arg, i, start, tmp);
		}
		cmd->msg = ft_strdup(tmp);
	}
	//printf("cmd->msg = %s\n", cmd->msg);
}

int	ft_which_cmd(char **cpy)
{
    if (ft_strncmp(cpy[0], "echo", ft_strlen(cpy[0])) == 0)
        return (1);
    return (0);
}

char	*ft_echo_msg(t_arg *arg, int i, int start, char *tmp)
{
	int	size;
	int	a;
	
	size = ft_strlen(arg->cmds[i]);
	//printf("size = %d start = %d i = %d cmds = %c\n", size, start, i, arg->cmds[i][start]);
	tmp = malloc(sizeof(char) * (size - start + 1));
	if (!tmp)
		return (NULL);
	a = 0;
	while (start < size)
	{
		tmp[a] = arg->cmds[i][start];
		a++;
		start++;
	}
	tmp[a] = '\0';
    return (tmp);
}