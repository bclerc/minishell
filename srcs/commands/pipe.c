/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/14 13:55:15 by bclerc           ###   ########.fr       */
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
    t_cmd *tmp;
    pid_t pid;

    int status;
    int nbpipe = get_pipe_count(cmd);
    int *pipes;
    int i;

    pipes = (int *)malloc(sizeof(int) * (nbpipe * 2));
    open_pipe(pipes, nbpipe);
    tmp = cmd;
    i = 0;
    while (tmp)
    {
        pid = fork();
        if (pid == 0) // processus enfant
        {
            if (cmd->next) // pas la derniere commande;
                dup2(pipes[i + 1], 1); // Copie la sortie standard i +1 (i augmente de 2, si 0 + 1 pour recuperer l'entree
            if (cmd != tmp) // si pas la premiere commande
                dup2(pipes[i - 2], 0); // copie l'entree standard i - 2 (i augmente de 2 si i = 2 i -2 = 0 entree standard
            close_fd(pipes, nbpipe); // On ferme les sortie du pipe, parce qu'on les utilises pas, ils sont la juste pour faire la lien entre le parent et le child
            execute_commands(tmp); // On execute la commande
        }
        tmp = tmp->next; // commande suivante
        i = i + 2;
    }
    close_fd(pipes, nbpipe); // Same line 81, on ferme les sorties du pipes.
    i = 0;
    while (i < nbpipe + 1)
    {
        wait(&status);  // On attends tous les processus childs
        i++;
    }
    return (1);
}
