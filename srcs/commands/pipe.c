/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:56 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/10 15:29:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_in_fd(int *pipes, t_cmd *cmd, int i)
{
	char	*here_doc;
	int		fd;

	if (cmd->redir != NULL && cmd->redir->fd_in != NULL)
	{
		if (cmd->redir->redir_std_in == REDIR_APPEND_IN)
		{
			here_doc = heredoc(cmd);
			fd = get_fd(here_doc,  0);
			free(here_doc);
		}
		else
			fd = get_fd(cmd->redir->fd_in, 0);
	}
	else
		fd = pipes[i - 2];
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

int	get_dup_fd(int *pipes, t_cmd *cmd, int i, int in, int nbpipes)
{
	char	*here_doc;
	int		fd;
	if (in)
		return (get_in_fd(pipes, cmd, i));
	if (cmd->redir && cmd->redir->fd_out != NULL)
	{
		if (cmd->redir->next)
			fd = mul_redir(cmd);
		else
			fd = get_fd(cmd->redir->fd_out, cmd->redir->redir_std_out);
	}
	else
		fd = pipes [i + 1];
	if (fd < 0)
	{
		printf("Minishell: Error on open FD\n");
		close_fd(pipes, nbpipes);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	set_in_out(int *pipes, t_cmd *cmd, t_cmd *first_cmd, int i, int nbpipes)
{
	int	fd;
	fd = 0;
	if (cmd != first_cmd || (cmd->redir && cmd->redir->fd_in))
	{
		fd = get_dup_fd(pipes, cmd, i, 1, nbpipes);
		if (dup2(fd, 0) <= -1)
			perror("dup2 (in)");
		close(fd);
	}
	if (cmd->next || (cmd->redir != NULL && cmd->redir->fd_out != NULL))
	{
		fd = get_dup_fd(pipes, cmd, i, 0, nbpipes);
		if (dup2(fd, 1) <= -1)
			perror("dup2 (out)");
		close(fd);
	}
	return (1);
}

int is_forkable(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->cmd, "unset") == 0  && cmd->msg != NULL)
		|| ft_strcmp(cmd->cmd, "export") == 0 && cmd->msg != NULL)
		return (0);
	return (1);
}

int	fork_cmd(int *pipes, t_cmd *cmd, int nbpipe)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		i;
	int		ret;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd == NULL)
		{
			tmp = tmp->next;
			continue;
		}
		if (ft_strcmp(tmp->cmd, "exit") == 0)
		{
			if (!tmp->next)
				return (0);
			else
				tmp = tmp->next;
		}
		if (is_forkable(tmp))
		{
			pid = fork();
			core->child_exist = 1;
			core->child = pid;
			if (pid == 0)
			{
				set_in_out(pipes, tmp, cmd, i, nbpipe);
				close_fd(pipes, nbpipe);
				ret = execute_commands(tmp);
			}
			i = i + 2;
		}
			else
		ret = execute_commands(tmp);
		tmp = tmp->next;
	}
	return (ret);
}

int	m_pipe(t_cmd *cmd)
{
	int		nbpipe;
	int		*pipes;
	int		i;
	int		status;

	pipes = 0;
	nbpipe = 0;
	status = 0;
	if ((ft_strcmp(cmd->cmd, "exit") == 0 && !cmd->next)
		|| ft_strcmp(cmd->cmd, "cd") == 0)
		return (execute_commands(cmd));
	nbpipe = get_pipe_count(cmd);
	pipes = (int *)malloc(sizeof(int) * (nbpipe * 2));
	if (!pipes)
		return (1);
	open_pipe(pipes, nbpipe);
	fork_cmd(pipes, cmd, nbpipe);
	close_fd(pipes, nbpipe);
	i = 0;
	while (i < nbpipe + 2)
	{
		wait(&status);
		i++;
	}
	free(pipes);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	return (status);
}
