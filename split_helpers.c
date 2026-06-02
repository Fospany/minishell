/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:09:28 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/02 13:00:33 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_for_quote(const char letter, int *quote_type)
{
    if (letter == SINGLE_QUOTE)
        return (*quote_type = SINGLE_QUOTE, 1);
    else if (letter == DOUBLE_QUOTE)
        return (*quote_type = DOUBLE_QUOTE, 1);
    else
        return (0);
}

int check_for_quote_without_quote_type(const char letter)
{
    if (letter == SINGLE_QUOTE)
        return (1);
    else if (letter == DOUBLE_QUOTE)
        return (1);
    else
        return (0);
}

int     is_terminator(const char letter)
{
    if (letter == '\0')
        return (1);
    return (0);
}

int     is_astrisk(const char letter)
{
    if (letter == '*')
        return (1);
    return (0);
}

int     letter_after_dollar_is_num_or_astrisk(const char letter)
{
    if (is_number(letter) || is_astrisk(letter))
        return (1);
    return (0);
}

int     dollar_is_standing_alone(const char letter)
{
    if (is_white_space(letter) || is_terminator(letter))
        return (1);
    return (0);
}

void     process_after_dollar_sign(const char *read_line, int *i, int *words)
{
    while (read_line[*i] && !is_white_space(read_line[*i]))
    {
        if (check_for_quote_without_quote_type(read_line[*i]))
        {
            (*words)++;
            return ;
        }
        else if (is_heredoc_or_append(read_line[*i], read_line[(*i) + 1]))
        {
            (*i) += 2;
            (*words) += 2;
            return ;
        }
        else if (is_redir_or_pipe(read_line[*i]))
        {
            (*i)++;
            (*words) += 2;
            return ;
        }
        (*i)++;
    }
    (*words)++;
}

int     is_dollar_sign(const char letter)
{
    if (letter == DOLLAR_SIGN)
        return (1);
    return (0);
}

int    dollar_sign_exception(const char *read_line, int *i, int *words)
{
    if (is_dollar_sign(read_line[*i]))
    {
        if (dollar_is_standing_alone(read_line[(*i) + 1]))
        {
            (*words)++;
            (*i) += 2;
        }
        else if (letter_after_dollar_is_num_or_astrisk(read_line[(*i) + 1]))
            (*i) += 2;
        else
            process_after_dollar_sign(read_line, i, words);
        return (1);
    }
    return (0);
}

int word_counter(const char *read_line)
{
    int i;
    int words;
    words = 0;
    i = 0;
    while (read_line[i])
    {
        skip_white_spaces(read_line, &i);
        quote_in_word(read_line, &i, &words);
        skip_white_spaces(read_line, &i);
        if (is_word_2(read_line, &i, &words) && read_line[i])
            words++;
    }
    return (words);
}

int     is_special_character(const char *read_line, int i, int *letters)
{
    if (is_heredoc_or_append(read_line[i], read_line[(i) + 1]))
    {
        if (*letters == 0)
            (*letters) += 2;
        return (1);
    }
    else if (is_redir_or_pipe(read_line[i]))
    {
        if (*letters == 0)
            (*letters)++;
        return (1);
    }
    return (0);
}


int     count_letters(const char *read_line, int i)
{
    int letters;

    letters = 0;
    while (read_line[i])
    {
        if (is_white_space(read_line[i]))
            return (letters);
        else if (check_for_quote_without_quote_type(read_line[i]) && letters > 0)
            return (letters);
        if (is_special_character(read_line, i, &letters))
            return (letters);
        i++;
        letters++;
    }
    return (letters);
}

void    split_clean_up(char **split_line, int i)
{
    int j;

    j = 0;
    while (j < i)
        free(split_line[j++]);
    free(split_line);
}
