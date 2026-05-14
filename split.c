/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:39:41 by rici              #+#    #+#             */
/*   Updated: 2026/05/14 17:37:24 by rici             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

int quote_check(char *text, int *i, char c)
{
    int index;

    index = *i;
    while (text[index])
    {
        if (text[index] == c)
        {
            *i = index;
            return (0);
        }
        index++;
    }
    return (1);
}

int is_whitespace(char c)
{
    if ((c < 14 && c > 8) || c == 32)
        return (1);
    return (0);
}

int word_counter(char *s)
{
    int i;
    int words;

    i = 0;
    words = 0;
    while (s[i])
    {
        while (s[i] && is_whitespace(s[i]))
            i++;
        if (s[i] && !is_whitespace(s[i]))
            words++;
        while (s[i] && !is_whitespace(s[i]))
        {
            if (s[i] == '\'' || s[i] == '\"')
            {
                if (quote_check(s, &i + 1, s[i]))
                    return (-1);
            }
            i++;
        }
    }
    return (words);
}

int letter_counter(char *word, int *i)
{
    int start;

    start = *i;
    while (is_whitespace(word[*i]))
        (*i)++;
    while (!is_whitespace(word[*i]))
    {
        if (word[*i] == '\'' || word[*i] == '\"')
            quote_check(word, i + 1, word[*i]);
        (*i)++;
    }
    return (*i - start);
}

char    *quote_fill(char *line, int *i, char c, int len)
{
    char *new_word;
    int l;

    l = 0;
    new_word = calloc(sizeof(char), (len + 1));
    if (!new_word)
        return (NULL);
    while (line[*i] != c)
    {
        new_word[l] = line[*i];
        (*i)++;
        l++;
    }
    return (new_word);
}

char    **fulfill(char *line, char **full_string, int *lens)
{
    int *i;
    int w;
    int l;

    i = 0;
    w = 0;
    l = 0;
    while (line[*i])
    {
        while (is_whitespace(line[*i]) && line[*i])
            i++;
        while (!is_whitespace(line[*i]) && line[*i])
        {
            if (line[*i] == '\'' || line[*i] == '\"')
                full_string[w] = quote_fill(line, &i, w, lens[w]);
        }
    }
}

char    **split(char *line)
{
    char **final_string;
    int words;
    int i;
    int index;
    int *lengths;
    int letters;

    i = 0;
    index = 0;
    words = word_counter(line);
    lengths = malloc(sizeof(int) * words);
    final_string = malloc(sizeof(char) * (word_counter(line) + 1));
    while (i < words)
    {
        letters = letter_counter(line, &index) + 1;
        final_string[i] = calloc(sizeof(char), letters);
        lengths[i] = letters;
        i++;
    }
}

int main(int args, char **argv)
{
    int words;

    words = word_counter(argv[1]);
    printf("%i\n", words);
    return (0);
}