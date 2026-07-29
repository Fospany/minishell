/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:32:32 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/29 13:36:54 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_heredoc(int write_fd, char *eof);

int	handle_in(t_cmds *curr, t_token *tokens, int *i)
{
	if (curr->fd_in != 0)
		close(curr->fd_in);
	curr->fd_in = open(tokens[*i + 1].value, O_RDONLY);
	if (curr->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tokens[*i + 1].value);
	}
	return (1);
}

int	handle_out(t_cmds *curr, t_token *token, int *i)
{
	if (curr->fd_out != 1)
		close(curr->fd_out);
	if (token[*i].type == token_redirect_out)
	{
		curr->fd_out = open(token[*i + 1].value, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (curr->fd_out == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(token[*i + 1].value);
		}
	}
	if (token[*i].type == token_append)
	{
		curr->fd_out = open(token[*i + 1].value, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (curr->fd_out == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(token[*i + 1].value);
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

static void	fill_heredoc(int write_fd, char *eof)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(eof) && ft_strncmp(line, eof,
					ft_strlen(eof)) == 0))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		ft_putchar_fd('\n', write_fd);
		free(line);
	}
}

int	handle_heredoc(t_cmds *curr, t_token *token, int *i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("minishell: "), 0);
	fill_heredoc(fd[1], token[*i + 1].value);
	close(fd[1]);
	if (curr->fd_in != 0)
		close(curr->fd_in);
	curr->fd_in = fd[0];
	return (1);
}
