/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguthy <bguthy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 14:02:51 by bguthy            #+#    #+#             */
/*   Updated: 2026/05/21 17:32:35 by bguthy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_to_next_quote(const char *read_line, char quote_type)
{
    int i;

    i = 0;
    while (*read_line++)
    {
        i++;
        if (*read_line == quote_type)
            break ;
    }
    i += skip_non_white_spaces(read_line + i);
    return (i + 1);
}

int is_white_space(const char letter)
{
    if ((letter <= CARRIAGE_RET && letter >= HORIZONTAL_TAB) || letter == SPACE)
        return (1);
    return (0);
}

int skip_white_spaces(const char *read_line)
{
    int i;

    i = 0;
    while (is_white_space(*read_line++))
        i++;
    return (i);
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

int is_word(const char *read_line, int *words)
{
    int i;

    i = 0;
    while (!is_white_space(*read_line) && *read_line++)
        i++;
    if (i != 0)
        (*words)++;
    return (i);
}

int word_counter(const char *read_line)
{
    int words;
    int quote_type;

    quote_type = 0;
    words = 0;
    while (*read_line)
    {
        read_line += skip_white_spaces(read_line);
        if(check_for_quote(*read_line, &quote_type))
        {
            words++;
            read_line += skip_to_next_quote(read_line + 1, quote_type);
        }
        read_line += is_word(read_line, &words);
    }
    return (words);
}

int     skip_non_white_spaces(const char *read_line)
{
    int skips;

    skips = 0;
    while (!is_white_space(*read_line) && *read_line)
    {
        read_line++;
        skips++;
    }
    return (skips);
}

int     count_letters(const char *read_line, int i)
{
    int start;
    int quote_type;

    quote_type = 0;
    start = i;
    if (check_for_quote(read_line[i], &quote_type))
    {
        i += skip_to_next_quote(read_line + 1, quote_type);
        return (i - start);
    }
    i += skip_non_white_spaces(read_line + i);
    return (i - start);
}

char    **allocating_double_pointer(const char *read_line)
{
    int words;
    char **split_line;

    words = word_counter(read_line);
    split_line = malloc(sizeof(char *) * (words + 1));   
    return (split_line);
}

char    *copy_n_chars(int start, int end, const char *read_line)
{
    int     i;
    char    *new_word;

    i = 0;
    new_word = malloc(sizeof(char) * (end - start + 1));
    if (!new_word)
        return (NULL);
    while (start < end)
        new_word[i++] = read_line[start++];
    new_word[i] = 0;
    return (new_word);
}

void    fill_up_double_pointer(char **split_line, const char *read_line)
{
    int start_of_word;
    int w;
    int end_of_word;
    int quote_type;

    quote_type = 0;
    w = 0;
    start_of_word = 0;
    end_of_word = 0;
    while (read_line[start_of_word])
    {
        start_of_word += skip_white_spaces(read_line + start_of_word);
        if (check_for_quote(read_line[start_of_word], &quote_type))
        {
            end_of_word = start_of_word + skip_to_next_quote(read_line + start_of_word, quote_type);
            split_line[w++] = copy_n_chars(start_of_word, end_of_word, read_line);
            start_of_word = end_of_word;
        }
        start_of_word += skip_white_spaces(read_line + start_of_word);
        end_of_word = start_of_word + count_letters(read_line, start_of_word);
        split_line[w++] = copy_n_chars(start_of_word, end_of_word, read_line);
        start_of_word = end_of_word;
    }
    split_line[w] = NULL;
}

char    **split(const char *read_line)
{
    char    **split_line;

    split_line = allocating_double_pointer(read_line);
    fill_up_double_pointer(split_line, read_line);
    return (split_line);
}

int main()
{
    char **okcso;
    int i;

    i = 0;
    okcso = split("okcso ''fasz''van geci lada      \0");
    while (okcso[i])
    {
        printf("%s\n", okcso[i]);
        free(okcso[i++]);
    }
    free(okcso);
    return (0);
}