/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:22:08 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/20 17:19:01 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*new_cmd(void)
{
	t_cmds	*new;

	new = ft_calloc(1, sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->fd_out = 1;
	return (new);
}

t_cmds	*add_cmd(t_cmds *head, t_cmds *new_list)
{
	t_cmds	*tmp;

	if (!new_list)
		return (NULL);
	if (!head)
	{
		head = new_list;
		return (head);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_list;
	return (head);
}

int	add_arg_to_cmd(t_cmds *node, char *arg)
{
	char	**tmp;
	int		count;
	int		i;

	if (!node)
		return (0);
	count = 0;
	i = -1;
	while (node->cmd && node->cmd[count])
		count++;
	tmp = ft_calloc(count + 2, sizeof(char *));
	if (!tmp)
		return (0);
	while (++i < count)
		tmp[i] = node->cmd[i];
	tmp[i] = ft_strdup(arg);
	if (!tmp[i])
		return (free_split(tmp), 0);
	free(node->cmd);
	node->cmd = tmp;
	return (1);
}

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
		if (!process_token(&head, &curr, tokens, &i))
			return (free_cmd(head), NULL);
		i++;
	}
	return (head);
}

int	process_token(t_cmds **head, t_cmds **curr, t_token *token, int *i)
{
	if (token[*i].type == token_word)
	{
		if (!add_arg_to_cmd(*curr, token[*i].value))
			return (0);
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
