/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 10:43:33 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/18 11:07:26 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(void)
{
	char buffer[PATH_MAX];
	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("pwd");
		return 1;
	}
	printf("%s\n", buffer);
	return 0;
}
