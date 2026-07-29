/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:53:25 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/29 13:40:18 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_flags(char **cmd);

int	echo(t_cmds *cmd)
{
	int	i;
	int	flags;

	flags = count_flags(cmd->cmd);
	i = 1 + flags;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!flags)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static int	count_flags(char **cmd)
{
	int	i;
	int	j;
	int	n_flags;

	i = 1;
	n_flags = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '-' || cmd[i][1] == '\0')
			break ;
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				break ;
			j++;
		}
		if (cmd[i][j] != '\0')
			break ;
		n_flags += 1;
		i++;
	}
	return (n_flags);
}
