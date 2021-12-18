/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:12:23 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/18 17:59:06 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void    del_env(void)
{
    t_env *tmp;

    while (core->env)
    {
        tmp = core->env->next;
        free(core->env->value);
        free(core->env);
        core->env = tmp;
    }
}

void    m_exit(t_cmd *cmd, int reason, char *function)
{
    int i;
    t_cmd *tmp;
    t_redir *redir;

    redir = cmd->redir;
    del_env();
    while (cmd)
    {
        while (cmd->redir)
        {
            redir = cmd->redir->next;
            free(cmd->redir->cmd_redir);
            free(cmd->redir->fd_in);
            free(cmd->redir->fd_out);
            free(cmd->redir);
            cmd->redir = redir;
        }
        tmp = cmd->next;
        free(cmd);
        cmd = tmp;
    }
    if (reason == M_EXIT_MALLOC_ERROR)
        printf("\nMinishell: Malloc error:\nFunction: %s\n", function);
}