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
static int	restore_io(int saved_stdin, int saved_stdout);

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
			return (perror("minishell: "), 1);
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

static int	restore_io(int saved_stdin, int saved_stdout)
{
	int	return_value;

	return_value = 0;
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		return_value = 1;
		perror("minishell: ");
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		return_value = 1;
		perror("minishell: ");
	}
	close(saved_stdin);
	close(saved_stdout);
	return (return_value);
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
