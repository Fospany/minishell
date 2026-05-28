/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stepping_in_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 20:34:44 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/28 12:23:43 by guthybarnak      ###   ########.fr       */
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
        if (is_redir_or_pipe(read_line[*i]))
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

int is_white_space_or_special_character(const char letter)
{
    if (is_white_space(letter) || is_redir_or_pipe(letter))
        return (1);
    return (0);
}

int check_for_pipe(const char *read_line, int *i)
{
    if (*i == 0 && is_white_space(read_line[1]))
        return ((*i)++, 1);
    else if (read_line[(*i) + 1] == '\0' && *i != 0 && is_white_space_or_special_character(read_line[(*i) - 1]))
        return ((*i)++, 1);
    else if (*i != 0 && is_white_space(read_line[(*i) - 1]) && is_white_space_or_special_character(read_line[(*i) + 1]))
        return ((*i)++, 1);
    else
        return (0);
}

int check_for_redirect_in_and_heredoc(const char *read_line, int *i)
{
    if (i == 0 && is_white_space(read_line[1]))
        return ((*i)++, 1);
    else if (i == 0 && read_line[1] == REDIR_IN && is_white_space(read_line[2]))
        return ((*i) += 2, 1);
    else if (i != 0 && is_white_space(read_line[(*i) - 1]) && is_white_space(read_line[(*i) + 1]))
        return ((*i)++, 1);
    else if (i != 0 && is_white_space(read_line[(*i) - 1]) && read_line[(*i) + 1] == REDIR_IN && is_white_space(read_line[(*i) + 2]))
        return ((*i) += 2, 1);
    else if (read_line[(*i) + 1] == '\0' && is_white_space(read_line[(*i) - 1]))
        return ((*i)++, 1);
    else if (read_line[(*i) + 2] == '\0' && read_line[(*i) + 1] == REDIR_IN && is_white_space(read_line[(*i) - 1]))
        return ((*i) += 2, 1);
    return (0);
}

int check_for_redirect_out_and_append(const char *read_line, int *i)
{
    if (i == 0 && is_white_space(read_line[1]))
        return ((*i)++, 1);
    else if (i == 0 && read_line[1] == REDIR_OUT && is_white_space(read_line[2]))
        return ((*i) += 2, 1);
    else if (i != 0 && is_white_space(read_line[(*i) - 1]) && is_white_space(read_line[(*i) + 1]))
        return ((*i)++, 1);
    else if (i != 0 && is_white_space(read_line[(*i) - 1]) && read_line[(*i) + 1] == REDIR_OUT && is_white_space(read_line[(*i) + 2]))
        return ((*i) += 2, 1);
    else if (read_line[(*i) + 1] == '\0' && is_white_space(read_line[(*i) - 1]))
        return ((*i)++, 1);
    else if (read_line[(*i) + 2] == '\0' && read_line[(*i) + 1] == REDIR_OUT && is_white_space(read_line[(*i) - 1]))
        return ((*i) += 2, 1);
    return (0);
}

int solo_standing_special_character(const char *read_line, int *i, int *words)
{
    if (is_pipe(read_line[*i]) && check_for_pipe(read_line, i))
        return ((*words)++, 1);
    else if (read_line[*i] == '<' && check_for_redirect_in_and_heredoc(read_line, i))
        return ((*words)++, 1);
    else if (read_line[*i] == '>' && check_for_redirect_out_and_append(read_line, i))
        return ((*words)++, 1);
    return (0);
}

int is_pipe(const char letter)
{
    if (letter == '|')
        return (1);
    return (0);
}

int is_redir(const char letter)
{
    if (letter == REDIR_IN || letter == REDIR_OUT)
        return (1);
    return (0);
}

int check_for_special_character(const char *read_line, int *i, int *words)
{
    if (is_pipe(read_line[*i]) && !is_redir_or_pipe(read_line[(*i) - 1]))
        return ((*words) += 2, (*i)++, 1);
    else if (is_pipe(read_line[*i]))
        return ((*words)++, (*i)++, 1);
    else if (is_heredoc_or_append(read_line[*i], read_line[(*i) + 1]) && !is_redir_or_pipe(read_line[(*i) - 1]))
        return ((*words) += 2, (*i) += 2, 1);
    else if (is_heredoc_or_append(read_line[*i], read_line[(*i) + 1]))
        return ((*words)++, (*i) += 2, 1);
    else if (is_redir(read_line[*i]) && !is_redir_or_pipe(read_line[(*i) - 1]))
        return ((*words) += 2, (*i)++, 1);
    else if (is_redir(read_line[*i]))
        return ((*words)++, (*i)++, 1);
}

int is_word_2(const char *read_line, int *i, int *words)
{
    int quote_type;
    
    quote_type = 0;
    while (!is_white_space(read_line[*i]) && read_line[*i])
    {
        if (solo_standing_special_character(read_line, i, words))
            return (0);
        else if (dollar_sign_exception(read_line, i, words))
            return (0);
        else if (quote_in_word(read_line, i, words))
            return (0);
        else if (check_for_special_character(read_line, i, words))
            return (0);
        (*i)++;
    }
    return (1);
}
