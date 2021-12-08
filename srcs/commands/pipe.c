/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/08 17:08:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int get_pipe_count(t_cmd *cmd)
{
    t_cmd *tmp;
    int     i;

    if (!cmd)
        return (-1);
    tmp = cmd;
    i = 0;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

int close_fd(int *tab_fd, int nb_pipes)
{
    int i;

    i = 0;
    while (i < nb_pipes * 2)
    {
        close(tab_fd[i]);
        i++;
    }
    return (1);
}

int open_pipe(int *tab_fd, int nb_pipes)
{
    int i;

    i = 0;
    while (i < nb_pipes)
    {
        pipe(tab_fd + i* 2);
        i++;
    }
    return (1);
}

int m_pipe(t_cmd *cmd)
{
    pid_t pid;
    int status;
    t_cmd *tmp;
    int i;
    int *tab_fd;

    tab_fd = (int *)malloc(sizeof(int) * (get_pipe_count(cmd)*2));
    tmp = cmd;
    open_pipe(tab_fd, get_pipe_count(cmd));
    i = 0;
    while (tmp)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("(%d) Executed cmd : %s\n", i-1, tmp->cmd);
            if (tmp->next)
                dup2(tab_fd[i + 1], 1);
            if (i)
                dup2(tab_fd[i - 2], 0);
            close_fd(tab_fd, get_pipe_count(cmd));
            execve(ft_strjoin("/bin/", tmp->cmd), get_argv(tmp), env_to_char());
            perror("ERROR: ");
        }
        tmp = tmp->next;
        i=+2;

    } 
    close_fd(tab_fd, get_pipe_count(cmd));
    i = 0;
    while (i < get_pipe_count(cmd) + 1)
    {
        wait(&status);
     
        i++;
    }
    exit(1);
}
