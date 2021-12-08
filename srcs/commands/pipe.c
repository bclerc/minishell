/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/08 19:15:51 by bclerc           ###   ########.fr       */
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
    int nbpipe;
    int i;
    int tab_fd[500];

    nbpipe = get_pipe_count(cmd);
    tmp = cmd;
    open_pipe(tab_fd, nbpipe);
    i = 0;
    while (tmp)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("(%d) Executed cmd : '%s %s'\n", i-1, tmp->cmd, tmp->msg);
            if (tmp->next)
                dup2(tab_fd[i + 1], 1);
            if (i != 0)
                dup2(tab_fd[i - 2], 0);
            close_fd(tab_fd, nbpipe);
            execve(ft_strjoin("/bin/", tmp->cmd), get_argv(tmp), env_to_char());
            perror("ERROR: ");
        }
        tmp = tmp->next;
        i=+2;
    }
    close_fd(tab_fd, nbpipe);
    i = 0;
    while (i < nbpipe + 1)
    {
        wait(NULL);
        i++;
    }
    exit(1);
}
