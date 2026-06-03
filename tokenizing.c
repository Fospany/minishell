/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:13:55 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/03 17:43:00 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenizer(char *input)
{
    if (env_assign_check(input))
        return token_env_assign;
    else if (string_compare(input, "|"))
        return token_pipe;
    else if (string_compare(input, ">>"))
        return token_append;
    else if (string_compare(input, "<<"))
        return token_heredoc;
    else if (string_compare(input, "<"))
        return token_redirect_in;
    else if (string_compare(input, ">"))
        return token_redirect_out;
    else
        return token_word;
}

void    create_token_struct(t_token *tokens, char **line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        tokens[i].value = line[i];
        tokens[i].type = tokenizer(line[i]);
        i++;
    }
    tokens[i].value = NULL;
    tokens[i].type = -1;
}
