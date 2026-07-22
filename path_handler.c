/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:53:03 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/20 17:06:26 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_status(int status, char *cmd);
static char	*format_path(char *cmd_name, char *path);

char	*handling_path(char *cmd_name, char *path)
{
	char	**split_path;
	char	*cmd_path;
	int		status;

	status = 0;
	if (ft_strncmp(cmd_name, "", 1) == 0)
		return NULL;
	if (ft_strchr(cmd_name, '/'))
	{
		status = check_access(cmd_name);
		cmd_path = ft_strdup(cmd_name);
		if (!cmd_path)
			return (NULL);
		if (status == 3)
			return (cmd_path);
		return (print_status(status, cmd_name), free(cmd_path), NULL);
	}
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	cmd_path = find_cmd_path(cmd_name, split_path, &status);
	free_split(split_path);
	if (!cmd_path)
		return (print_status(status, cmd_name), NULL);
	return (cmd_path);
}

void	free_split(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*format_path(char *cmd_name, char *path)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd_name);
	if (!cmd_path)
		return (free(tmp), NULL);
	return (cmd_path);
}

char	*find_cmd_path(char *cmd_name, char **split_path, int *status)
{
	char	*cmd_path;
	int		i;
	int		curr_status;

	curr_status = 0;
	i = 0;
	cmd_path = NULL;
	while (split_path[i])
	{
		cmd_path = format_path(cmd_name, split_path[i]);
		if (!cmd_path)
			return (NULL);
		curr_status = check_access(cmd_path);
		if (curr_status > *status)
			*status = curr_status;
		if (*status == 3)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	return (NULL);
}

static void	print_status(int status, char *cmd)
{
	if (status == 0)
	{
		if (ft_strchr(cmd, '/'))
			print_error("No such file or directory", cmd, 2);
		else
			print_error("command not found", cmd, 2);

	}
	else if (status == 1)
		print_error("is a directory", cmd, 2);
	else if (status == 2)
		print_error("Permission denied", cmd, 2);
}

int is_dir(char *cmd, struct stat *path_stat)
{
	if (stat(cmd, path_stat) == 0)
	{
		if ((path_stat->st_mode & S_IFMT) == S_IFDIR)
			return 1;
	}
	return 0;
}

int	check_access(char *cmd)
{
	int	status;
	struct stat path_stat;

	status = 0;
	if (is_dir(cmd, &path_stat))
	{
		status = 1;
		return status;
	}
	if (access(cmd, F_OK) == 0)
	{
		status = 2;
		if (access(cmd, X_OK) == 0)
			status = 3;
	}
	return (status);
}

void	print_error(char *msg, char *cmd, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(msg, fd);
	ft_putchar_fd('\n', fd);
}
