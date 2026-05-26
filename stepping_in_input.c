/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stepping_in_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 20:34:44 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/26 22:29:00 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_white_space(const char letter)
{
    if ((letter <= CARRIAGE_RET && letter >= HORIZONTAL_TAB) || letter == SPACE)
        return (1);
    return (0);
}

void skip_white_spaces(const char *read_line, int *i)
{
    while (is_white_space(read_line[*i]))
        (*i)++;
}

void skip_to_next_quote(const char *read_line, int *i, char quote_type)
{
    while (read_line[*i])
    {
        (*i)++;
        if (read_line[*i] == quote_type)
        {
            (*i)++;
            break ;
        }
    }
    skip_non_white_spaces(read_line, i);
}

void     skip_non_white_spaces(const char *read_line, int *i)
{
    while (!is_white_space(read_line[*i]) && read_line[*i])
    {
        if (is_special_character(read_line[*i], read_line[(*i) + 1]))
            break ;
        (*i)++;
    }
}

int     is_redir_or_pipe(const char letter)
{
    if (letter == PIPE || letter == REDIR_IN || letter == REDIR_OUT)
        return (1);
    return (0);
}

int     is_heredoc_or_append(const char letter1, const char letter2)
{
    if (letter1 == REDIR_IN && letter2 == REDIR_IN)
        return (1);
    else if (letter1 == REDIR_OUT && letter2 == REDIR_OUT)
        return (1);
    return (0);
}

int     special_characters_exception(const char *read_line, int *i, int *words)
{
    if (read_line[*i] == DOLLAR_SIGN)
        return (dollar_sign_exception(read_line, i, words), 1);
    if (is_heredoc_or_append(read_line[*i], read_line[(*i) + 1]))
    {
        (*words) += 2;
        (*i) += 2;
        return (1);
    }
    else if (is_redir_or_pipe(read_line[*i]))
    {
        (*words) += 2;
        (*i)++;
        return (1);
    }
    return (0);
}

int valid_index_for_spec_char(const char letter, int num1, int num2)
{
    if (num1 == num2 && is_white_space(letter))
        return (0);
    else
        return (1);
}

int quote_in_word(const char *read_line, int *i, int *words)
{
    int quote_type;
    
    quote_type = 0;
    if (check_for_quote(read_line[*i], &quote_type))
    {
        skip_to_next_quote(read_line, i, quote_type);
        (*words)++;
        return (1);
    }
    return (0);
}

int is_word(const char *read_line, int *i, int *words)
{
    int start;
    int flag;
    
    start = *i;
    flag = 0;
    while (!is_white_space(read_line[*i]) && read_line[*i])
    {
        if (quote_in_word(read_line, i, words))
            return (0);
        if (valid_index_for_spec_char(read_line[(*i) + 1], *i, start) && special_characters_exception(read_line, i, words))
        {
            flag = 1;
            if (is_white_space(read_line[*i]))
                return (0);
        }
        else
            (*i)++;
    }
    if (flag && !read_line[*i])
        return (0);
    else
        return (1);
}
