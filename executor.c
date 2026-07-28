/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 09:57:52 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/28 11:42:23 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_pipe(t_cmds *cmds, int *fd, int *stored_input, char **envp);

int	execute_cmds(t_cmds *cmds, char **envp)
{
	t_cmds	*tmp;
	int		fd[2];
	int		status;
	int		stored_input;

	status = 0;
	stored_input = -1;
	ft_bzero(fd, 2);
	tmp = cmds;
	if (!cmds->next)
	{
		single_built_in(cmds, envp, &status);
		return (status);
	}
	while (cmds)
	{
		if (!fork_pipe(cmds, fd, &stored_input, envp))
			return (0);
		clean_parent(cmds, fd, &stored_input);
		cmds = cmds->next;
	}
	wait_pids(tmp, &status);
	return (status);
}

int	single_built_in(t_cmds *cmds, char **envp, int *status)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmds->fd_in != 0)
		safe_dup2(cmds->fd_in, STDIN_FILENO);
	if (cmds->fd_out != 1)
		safe_dup2(cmds->fd_out, STDOUT_FILENO);
	if (is_built_in(cmds->cmd[0]))
		*status = run_built_in(cmds, envp);
	else
	{
		if (!single_exec(cmds, envp, status))
			return (0);
	}
	safe_dup2(saved_stdin, STDIN_FILENO);
	safe_dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

int	single_exec(t_cmds *cmd, char **envp, int *status)
{
	char	*path;

	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	path = handling_path(cmd->cmd[0], envp[find_path(envp)]);
	if (!path)
		return (0);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("minishell: "), 0);
	if (cmd->pid == 0)
	{
		if (cmd->fd_in != 0)
			safe_dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out != 1)
			safe_dup2(cmd->fd_out, STDOUT_FILENO);
		execve(path, cmd->cmd, envp);
		exit(1);
	}
	waitpid(cmd->pid, status, 0);
	return (1);
}

static int	fork_pipe(t_cmds *cmds, int *fd, int *stored_input, char **envp)
{
	if (cmds->next)
	{
		if (pipe(fd) == -1)
			return (0);
	}
	cmds->pid = fork();
	if (cmds->pid == 0)
		run_child(cmds, fd, *stored_input, envp);
	return (1);
}
