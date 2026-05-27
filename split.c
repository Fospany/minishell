/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 14:02:51 by bguthy            #+#    #+#             */
/*   Updated: 2026/05/27 08:48:52 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char    *copy_till_next_word(const char *read_line, int *i)
{
    int     letters;
    int     local_index;
    char    *new_word;
    
    local_index = 0;
    letters = count_letters(read_line, *i);
    new_word = malloc(sizeof(char) * (letters + 1));
    if (!new_word)
        return (NULL);
    while (!is_white_space(read_line[*i]) && read_line[*i])
    {
        new_word[local_index++] = read_line[(*i)++];
        if (is_heredoc_or_append(read_line[*i], read_line[(*i) + 1]) && local_index > 0)
            break ;
        else if ((is_redir_or_pipe(read_line[*i]) && local_index > 0 && !is_redir_or_pipe(new_word[local_index - 1])) || (is_redir_or_pipe(new_word[local_index - 1])))
            break ;
    }
    new_word[local_index] = 0;
    return (new_word);
}

char    *copy_till_next_quote(const char *read_line, int *i, int quote_type)
{
    char    *new_word;
    int     temp;
    int     local_index;

    local_index = 0;
    temp = *i;
    skip_to_next_quote(read_line, i, quote_type);
    new_word = malloc(sizeof(char) * (*i - temp + 1));
    while (temp < *i)
        new_word[local_index++] = read_line[temp++];
    new_word[local_index] = 0;
    return (new_word);
}

char    **allocating_double_pointer(const char *read_line)
{
    int     words;
    char    **split_line;
    
    words = word_counter(read_line);
    split_line = malloc(sizeof(char *) * (words + 1));
    return (split_line);
}

void    fill_up_double_pointer(char **split_line, const char *read_line)
{
    int i;
    int w;
    int quote_type;

    i = 0;
    quote_type = 0;
    w = 0;
    while (read_line[i])
    {
        skip_white_spaces(read_line, &i);
        if (check_for_quote(read_line[i], &quote_type))
            split_line[w++] = copy_till_next_quote(read_line, &i, quote_type);
        if (!is_white_space(read_line[i]) && read_line[i])
            split_line[w++] = copy_till_next_word(read_line, &i);
        if (split_line[w - 1] == NULL)
            return (split_clean_up(split_line, w));
    }
    split_line[w] = NULL;
}

char    **split(const char *read_line)
{
    char    **split_line;

    split_line = allocating_double_pointer(read_line);
    if (!split_line)
        return (NULL);
    fill_up_double_pointer(split_line, read_line);
    return (split_line);
}
