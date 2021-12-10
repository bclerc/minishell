/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/10 16:01:26 by bclerc           ###   ########.fr       */
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
    return (i - 1);
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
        pipe(tab_fd + i * 2);
        i++;
    }
    return (1);
}

int m_pipe(t_cmd *cmd)
{
    pid_t pid;
    int status;
    t_cmd *tmp;
    int nbpipe;
    int i;
    int tab_fd[2];

    nbpipe = get_pipe_count(cmd);
    tmp = cmd;
    i = 0;
    while (tmp)
    {
        if (tmp->next)
            pipe(tab_fd);
        pid = fork();
        if (pid == 0)
        {
            if (tmp->next)
            {
                dup2(tab_fd[1], 1);
                close(tab_fd[0]);
                close(tab_fd[1]);
            }
            if (execve(ft_strjoin("/bin/", tmp->cmd), get_argv(tmp), env_to_char()) < 0)
            {
                perror("ERROR: ");
                exit(-1);
            }
        }
        if (tmp->next)
        {
            dup2(tab_fd[0], 0);
            close(tab_fd[0]);
            close(tab_fd[1]);
        }
       // waitpid(-1);
        tmp = tmp->next;
        i=+2;
    }
    exit(1);
}
