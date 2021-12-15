/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/15 15:21:01 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int set_in_out(int *pipes, t_cmd *cmd, t_cmd *first_cmd, int i)
{
    if (cmd->next) // pas la derniere commande;
    {
        // Copie la sortie standard i +1 (i augmente de 2, si 0 + 1 pour recuperer l'entree
        if (dup2(pipes[i + 1], 1) <= -1)
        {
            perror("ERROR (dup2 fd <- 1)");
            printf("On cmd : \"%s %s\"", cmd->cmd, cmd->msg);
        }
    } 
    if (cmd != first_cmd)
    {
        int ret;
        if (ret = dup2(pipes[i - 2], 0) <= -1) // copie l'entree standard i - 2 (i augmente de 2 si i = 2 i -2 = 0 entree standard
        {
            perror("ERROR (dup2 0 -> fd)");
            printf("On cmd : \"%s %s\"", cmd->cmd, cmd->msg);
        }
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
    int fd1 = open("foo", O_RDONLY);
    while (tmp)
    {
        pid = fork();
        if (pid == 0) // processus enfant
        {
            set_in_out(pipes, tmp, cmd, i);
            close_fd(pipes, nbpipe); // On ferme les sortie du pipe, parce qu'on les utilises pas, ils sont la juste pour faire la lien entre le parent et le child
            execute_commands(tmp); // On execute la commande
        }
        tmp = tmp->next; // commande suivante
        i = i + 2;
    }
    close_fd(pipes, nbpipe); // Same line 81, on ferme les sorties du pipes.
    i = 0;
    while (i < nbpipe + 2)
    {
        wait(&status);  // On attends tous les processus childs
        i++;
    }
    return (1);
}
