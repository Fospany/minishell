/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 10:02:58 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/29 13:29:44 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_redirections(t_cmds *cmds, int *fd, int stored_input);

void	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("minishell: ");
		exit(1);
	}
}

void	run_child(t_cmds *cmds, int *fd, int stored_input, char **envp)
{
	char	*path;

	if (!cmds->cmd || !cmds->cmd[0])
		exit(0);
	if (cmds->fd_in == -1 || cmds->fd_out == -1)
		exit(1);
	child_redirections(cmds, fd, stored_input);
	if (is_built_in(cmds->cmd[0]))
		exit(run_built_in(cmds, envp));
	path = handling_path(cmds->cmd[0], envp[find_path(envp)]);
	if (!path)
		exit(127);
	execve(path, cmds->cmd, envp);
	perror("minishell: ");
	exit(1);
}

void	clean_parent(t_cmds *cmds, int *fd, int *stored_input)
{
	if (*stored_input != -1)
		close(*stored_input);
	if (cmds->fd_in != 0)
		close(cmds->fd_in);
	if (cmds->fd_out != 1)
		close(cmds->fd_out);
	if (cmds->next)
	{
		close(fd[1]);
		*stored_input = fd[0];
	}
}

void	wait_pids(t_cmds *cmds, int *status)
{
	while (cmds)
	{
		if (cmds->pid > 0)
			waitpid(cmds->pid, status, 0);
		cmds = cmds->next;
	}
}

static void	child_redirections(t_cmds *cmds, int *fd, int stored_input)
{
	if (stored_input != -1)
	{
		safe_dup2(stored_input, STDIN_FILENO);
		close(stored_input);
	}
	if (cmds->next)
	{
		safe_dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (cmds->fd_in != 0)
	{
		safe_dup2(cmds->fd_in, STDIN_FILENO);
		close(cmds->fd_in);
	}
	if (cmds->fd_out != 1)
	{
		safe_dup2(cmds->fd_out, STDOUT_FILENO);
		close(cmds->fd_out);
	}
}
