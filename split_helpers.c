/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:09:28 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/26 22:55:53 by guthybarnak      ###   ########.fr       */
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

int     is_valid_for_dollar_sign(const char letter)
{
    if (is_not_lower_case(letter) && is_not_upper_case(letter) && is_not_underline(letter))
        return (0);
    return (1);
}

int     letter_after_dollar_is_valid(const char letter)
{
    if (!is_valid_for_dollar_sign(letter) && is_not_number(letter))
        return (0);
    return (1);
}

void    dollar_sign_exception(const char *read_line, int *i, int *words)
{
    int quote_type;
    
    quote_type = 0;
    while (read_line[*i])
    {
        if (!letter_after_dollar_is_valid(read_line[++(*i)]))
            return ;
        if(check_for_quote(read_line[*i], &quote_type))
        {
            skip_to_next_quote(read_line, i, quote_type);
            words++;
            return ;
        }
        if (!is_valid_for_dollar_sign(read_line[*i]))
        {
            (*words)++;
            (*i)++;
            return ;
        }
        else
            (*i)++;
    }
}

int word_counter(const char *read_line)
{
    int i;
    int words;
    int quote_type;

    quote_type = 0;
    words = 0;
    i = 0;
    while (read_line[i])
    {
        skip_white_spaces(read_line, &i);
        quote_in_word(read_line, &i, &words);
        if (is_word(read_line, &i, &words))
            words++;
    }
    return (words);
}

int     is_special_character(const char letter1, const char letter2)
{
    if (letter1 == 0)
    {
        if (is_redir_or_pipe(letter1));
            return (1);
    }
    else if (is_heredoc_or_append(letter1, letter2) || is_redir_or_pipe(letter1))
        return (1);
    return (0);
}


int     count_letters(const char *read_line, int i)
{
    int letters;

    letters = 0;
    while (!is_white_space(read_line[i]) && read_line[i])
    {
        if (is_special_character(read_line[i], read_line[i + 1]))
        {
            if (letters == 0)
                return (1);
            else
                return (letters);
        }
        letters++;
        i++;
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
