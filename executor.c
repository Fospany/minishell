/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 09:57:52 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/22 20:33:27 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cmds(t_cmds *cmds, char **envp)
{
	int status;

	status = 0;
	if (!cmds->next)
	{
		single_exec(cmds, envp, &status);
		return status;
	}
	return status;
}

int find_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return i;
		i++;
	}
	return (0);
}

int single_built_in(t_cmds *cmds, char **envp, int *status)
{
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	if (cmds->fd_in != 0)
		dup2(cmds->fd_in, STDIN_FILENO);//fail check
	if (cmds->fd_out != 1)
		dup2(cmds->fd_out, STDOUT_FILENO);//fail check
	if (is_built_in(cmds->cmd[0]))
	{
		//run built in
		// restore stdin, out
		// return
	}
	single_exec(cmds, envp, status);
	dup2(saved_stdin, STDIN_FILENO);//fail check
	dup2(saved_stdout, STDOUT_FILENO);//fail check
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

int single_exec(t_cmds *cmd, char **envp, int *status)
{
	char *path;

	path = handling_path(cmd->cmd[0], envp[find_path(envp)]);//fail check
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("minishell: ");
		return (0);
	}
	if (cmd->pid == 0)
	{
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, STDIN_FILENO);//fail check
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, STDOUT_FILENO);//fail check
		execve(path, cmd->cmd, envp);
		exit(1);
	}
	waitpid(cmd->pid, status, 0);
	return (1);
}
