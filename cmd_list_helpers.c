/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:55:37 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/22 09:51:12 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmds *cmds)
{
	t_cmds	*curr;
	t_cmds	*next;

	if (!cmds)
		return ;
	curr = cmds;
	while (curr)
	{
		next = curr->next;
		free_split(curr->cmd);
		free(curr);
		curr = next;
	}
	curr = NULL;
}

int	handle_in(t_cmds *curr, t_token *tokens, int *i)
{
	if (curr->fd_in != 0)
		close(curr->fd_in);
	curr->fd_in = open(tokens[*i + 1].value, O_RDONLY);
	if (curr->fd_in == -1)
	{
		perror("minishell: ");
		return (0);
	}
	return (1);
}

int	handle_out(t_cmds *curr, t_token *tokens, int *i)
{
	if (curr->fd_out != 1)
		close(curr->fd_out);
	if (tokens[*i].type == token_redirect_out)
	{
		curr->fd_out = open(tokens[*i + 1].value, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (curr->fd_out == -1)
		{
			perror("minishell: ");
			return (0);
		}
	}
	if (tokens[*i].type == token_append)
	{
		curr->fd_out = open(tokens[*i + 1].value, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (curr->fd_out == -1)
		{
			perror("minishell: ");
			return (0);
		}
	}
	return (1);
}

int	handle_pipe(t_cmds **head, t_cmds **curr)
{
	t_cmds	*next;

	next = NULL;
	next = new_cmd();
	if (!next)
		return (0);
	*head = add_cmd(*head, next);
	if (!*head)
		return (0);
	*curr = next;
	return (1);
}


// int handle_heredoc(t_cmds *curr, t_token *token, int *i)
// {
// 	char *line;

// 	line = NULL;
// 	while ((line = readline("> ")))
// 	{

// 	}
// 	return (1);
// }
