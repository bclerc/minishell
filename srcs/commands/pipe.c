/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/23 11:54:21 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int get_dup_fd(int *pipes, t_cmd *cmd, int i, int in)
{
    int fd;
    char *here_doc;

    if (in)
    {
        if (cmd->redir && cmd->redir->fd_in != NULL)
        {
            if (cmd->std == REDIR_APPEND_IN)
            {
                here_doc = heredoc(cmd);
                fd = get_fd(here_doc);
                free(here_doc);
            }
            else
                fd = get_fd(cmd->redir->fd_in);
        }
        else
            fd = pipes[i - 2];
        if (fd < 0)
            exit(EXIT_FAILURE);
        return (fd);
    }
    if (cmd->redir && cmd->redir->fd_out != NULL)
        fd = get_fd(cmd->redir->fd_out);
    else
        fd = pipes [i + 1];
    if (fd < 0)
    {
        printf("Minishell: Error on open FD\n");
        exit(EXIT_FAILURE);
    }
    return (fd);
}
int set_in_out(int *pipes, t_cmd *cmd, t_cmd *first_cmd, int i)
{
    int fd;

        printf("OUT:%s\n", cmd);
    if (cmd->next || (cmd->redir && cmd->redir->fd_out)) // pas la derniere commande;
    {
        fd = get_dup_fd(pipes, cmd, i, 0);
        if (dup2(fd, 1) <= -1)
        {
            perror("ERROR (dup2 fd <- 1)");
            printf("On cmd : \"%s %s\"", cmd->cmd, cmd->msg);
        }
        close(fd);
    } 
    if (cmd != first_cmd || (cmd->redir && cmd->redir->fd_in))
    {
        fd = get_dup_fd(pipes, cmd, i, 1);
        if (dup2(fd, 0) <= -1) // copie l'entree standard i - 2 (i augmente de 2 si i = 2 i -2 = 0 entree standard
        {
            perror("ERROR 7874");
            printf("On cmd : \"%s %s\"", cmd->cmd, cmd->msg);
        }
        close(fd);
    } 
    return (1);
}

int m_pipe(t_cmd *cmd)
{
    t_cmd   *tmp;
    pid_t   pid;
    int     status;
    int     nbpipe;
    int     *pipes;
    int     i;

    if (ft_strcmp(cmd->cmd, "exit") == 0 || 
        ft_strcmp(cmd->cmd, "cd") == 0)
        return (execute_commands(cmd));
    nbpipe = get_pipe_count(cmd);
    pipes = (int *)malloc(sizeof(int) * (nbpipe * 2));
    open_pipe(pipes, nbpipe);
    tmp = cmd;
    i = 0;
    while (tmp)
    {
        pid = fork();
        core->child_exist = 1;
        core->child = pid;
        if (pid == 0)
        {
            set_in_out(pipes, tmp, cmd, i);
            close_fd(pipes, nbpipe);
            execute_commands(tmp);
        }
        tmp = tmp->next;
        i = i + 2;
    }
    close_fd(pipes, nbpipe);
    i = 0;
    while (i < nbpipe + 2)
    {
        wait(&status);
        i++;
    }
    free(pipes);
    return (1);
}
