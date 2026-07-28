/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:15:38 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/28 12:06:22 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	int		i;
	char	**bi;

	if (!cmd)
		return (0);
	i = 0;
	bi = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit",
		NULL};
	while (bi[i])
	{
		if (ft_strlen(bi[i]) == ft_strlen(cmd) && (ft_strncmp(bi[i], cmd,
					ft_strlen(bi[i])) == 0))
			return (1);
		i++;
	}
	return (0);
}

int	run_built_in(t_cmds *cmd, char **envp)
{
	(void)envp;
	if (ft_strlen(cmd->cmd[0]) == 3 && ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (pwd());
	if (ft_strlen(cmd->cmd[0]) == 4 && ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		return (echo(cmd));
	return (0);
}
