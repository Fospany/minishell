/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:09:28 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/29 18:32:45 by rici             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    set_quote_type(const char letter)
{
    int quote_type;
    
    quote_type = 0;
    if (letter == SINGLE_QUOTE)
        quote_type = SINGLE_QUOTE;
    else if (letter == DOUBLE_QUOTE)
        quote_type = DOUBLE_QUOTE;
    return (quote_type);
}

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
    return (0);
}

int     letter_after_dollar_is_num_or_astrisk(const char letter)
{
    if (is_number(letter) || is_astrisk(letter))
        return (1);
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
        if (read_line[i] && is_word_2(read_line, &i, &words))
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
