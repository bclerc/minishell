/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/07 17:02:25 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"


int m_pipe(t_cmd *cmd)
{
    int *fd;
    int fdd;
    t_cmd *tmp;
    pid_t pid;
    int nb_cmd = 0;
    int i = 0;
    int cmd_count = 0;
    int count = 0;
    int status;
    tmp = cmd;
    while (tmp)
    {
        nb_cmd++;
        tmp = tmp->next;
    }
    fd = malloc(sizeof(int) * nb_cmd);
    while (i < nb_cmd)
    {
        pipe(fd + i * 2);
        i++;
    }
    tmp = cmd;
    while (tmp)
    {
        pid = fork();
        if (pid == 0)
        {
            if (tmp->next)
            {
              dup2(fd[count + 1], 1);
                printf("DUP2\n");
            }
            if (count != 0)
            {
                printf("DUP1\n");
                dup2(fd[count - 2], 0);
            }
            i = 0;
            while (i < 2 * nb_cmd)
            {
                close(fd[i]);
                i++;
            }
            execve(ft_strjoin("/bin/", cmd->cmd), get_argv(cmd), env_to_char());
            perror("hello ");
        }
            tmp = tmp->next;
        count+= 2;
    }
    i = 0;
    while (i < 2 * nb_cmd)
    {
        printf("ICI\n");
        close(fd[i]);
        i++;
    }
    i = 0;
    while (i < nb_cmd + 1)
    {

        printf("ET ICI\n");
        wait(&status);
        i++;
    }
}
