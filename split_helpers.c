/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:09:28 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/22 10:45:35 by bguhty           ###   ########.fr       */
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
        if(check_for_quote(read_line[i], &quote_type))
        {
            skip_to_next_quote(read_line, &i, quote_type);
            words++;
        }
        if (is_word(read_line, &i))
            words++;
    }
    return (words);
}

int     count_letters(const char *read_line, int i)
{
    int letters;

    letters = 0;
    while (!is_white_space(read_line[i++]))
        letters++;
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