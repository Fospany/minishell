/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:08:24 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/20 16:12:08 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_check(t_token *tokens, int last)
{
    if (tokens[0].type == token_pipe)
        return (1);
    else if (tokens[last].type == token_pipe)
        return (1);
    return (0);
}

int redir_check(t_token *tokens, int i)
{
    if (tokens[i].type == token_append && tokens[i + 1].type != token_word)
        return (1);
    else if (tokens[i].type == token_redirect_in && tokens[i + 1].type != token_word)
        return (1);
    else if (tokens[i].type == token_redirect_out && tokens[i + 1].type != token_word)
        return (1);
    return (0);
}

int heredoc_check(t_token *tokens, int args)
{
    if (tokens[0].type == token_heredoc && args == 2)
        return (1);
    else if (tokens[args - 1].type == token_heredoc)
        return (1);
    return (0);
}

int syntax_check(t_token *tokens, int args)
{
    int i;
    
    i = 0;
    if (pipe_check(tokens, args - 1))
        return (1);
    if (heredoc_check(tokens, args))
        return (1);
    while (i < args - 2)
    {
        if (redir_check(tokens, i))
            return (1);
        i++;
    }
    return (0);
}
