/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 09:57:52 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/29 13:56:57 by dabdulla         ###   ########.fr       */
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

	if (!cmds)
		return (0);
	status = 0;
	stored_input = -1;
	ft_bzero(fd, 2);
	tmp = cmds;
	if (!cmds->next)
	{
		single_built_in(cmds, envp, &status);
		clean_parent(cmds,fd, &stored_input);
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

	if (!cmds->cmd)
		return (0);
	if (cmds->fd_in == -1 || cmds->fd_out == -1)
		return (1);
	if (is_built_in(cmds->cmd[0]))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdin == -1 || saved_stdout == -1)
			return (print_error(strerror(errno), cmds->cmd[0], 2), 1);
		if (change_io(cmds))
		{
			restore_io(saved_stdin, saved_stdout);
			return (1);
		}
		*status = run_built_in(cmds, envp);
		restore_io(saved_stdin, saved_stdout);
	}
	else
	{
		if (!run_cmd(cmds, envp, status))
			return (0);
	}
	return (0);
}

int	run_cmd(t_cmds *cmd, char **envp, int *status)
{
	char	*path;

	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	path = handling_path(cmd->cmd[0], envp[find_path(envp)]);
	if (!path)
		return (0);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (print_error(strerror(errno), cmd->cmd[0], 2), 0);
	if (cmd->pid == 0)
	{
		if (cmd->fd_in != 0)
		{
			safe_dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != 1)
		{
			safe_dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		execve(path, cmd->cmd, envp);
		exit(1);
	}
	waitpid(cmd->pid, status, 0);
	return (1);
}

void	run_child(t_cmds *cmds, int *fd, int stored_input, char **envp)
{
	char	*path;

	if (!cmds->cmd || !cmds->cmd[0])
		exit(0);
	if (cmds->fd_in == -1 || cmds->fd_out == -1)
		exit(1);
	child_redirections(cmds, fd, stored_input);
	close_inherited_fds(cmds);
	if (is_built_in(cmds->cmd[0]))
		exit(run_built_in(cmds, envp));
	path = handling_path(cmds->cmd[0], envp[find_path(envp)]);
	if (!path)
		exit(127);
	path = NULL;
	execve(path, cmds->cmd, envp);
	print_error(strerror(errno), cmds->cmd[0], 2);
	exit(1);
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
