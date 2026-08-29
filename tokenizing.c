/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:13:55 by bguhty            #+#    #+#             */
/*   Updated: 2026/08/28 19:56:50 by dabdulla         ###   ########.fr       */
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

const char    *create_exit_code()
{
    const char  *exit_code;

    exit_code = malloc(sizeof(char) * (10));
    if (!exit_code)
        return (NULL);
    exit_code = "exit_code\0";
    return (exit_code);
}

void    create_token_struct(t_token *tokens, char **line)
{
    int i;

    i = 0;
    // tokens[i].value = create_exit_code();
    // tokens[i].type = EXIT_SUCCESS;
    while (line[i])
    {
        tokens[i].value = line[i];
        tokens[i].type = tokenizer(line[i]);
        i++;
    }
    tokens[i].value = NULL;
    tokens[i].type = -1;
}
