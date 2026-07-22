/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 10:02:58 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/22 10:19:05 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_built_in(char *cmd)
{
	int i;
	char **bi;

	if (!cmd)
		return (0);
	i = 0;
	bi = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	while (bi[i])
	{
		if (ft_strncmp(bi[i], cmd, ft_strlen(cmd)) == 0)
			return (1);
		i++;
	}
	return (0);

}
