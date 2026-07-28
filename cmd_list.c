/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:22:08 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/28 10:34:15 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*build_cmds(t_token *tokens)
{
	t_cmds	*head;
	t_cmds	*curr;
	int		i;

	i = 0;
	curr = new_cmd();
	if (!curr)
		return (NULL);
	head = curr;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == token_word)
		{
			if (!add_arg_to_cmd(curr, tokens[i].value))
				return (free_cmd(head), NULL);
		}
		else if (!process_token(&head, &curr, tokens, &i))
			return (free_cmd(head), NULL);
		i++;
	}
	return (head);
}

int	process_token(t_cmds **head, t_cmds **curr, t_token *token, int *i)
{
	if (token[*i].type == token_heredoc)
	{
		if (!handle_heredoc(*curr, token, i))
			return (0);
		(*i)++;
	}
	else if (token[*i].type == token_redirect_in)
	{
		if (!handle_in(*curr, token, i))
			return (0);
		(*i)++;
	}
	else if (token[*i].type == token_redirect_out
		|| token[*i].type == token_append)
	{
		if (!handle_out(*curr, token, i))
			return (0);
		(*i)++;
	}
	else if (token[*i].type == token_pipe)
	{
		if (!handle_pipe(head, curr))
			return (0);
	}
	return (1);
}
