/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/22 10:24:59 by bguhty           ###   ########.fr       */
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

void    create_structs(t_token *tokens, char **line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        tokens[i].id = i;
        tokens[i].value = line[i];
        tokens[i].type = tokenizer(line[i]);
        i++;
    }
}

int equal_sign_check(char *string)
{
    int i;
    
    i = 0;
    while (string[i])
    {
        if (string[i] == EQUAL_SIGN)
            return (1);
        i++;
    }
    return (0);
}

int env_assign_check(char *string)
{
    int i;

    i = 0;
    if (!equal_sign_check(string))
        return (0);
    if (!first_letter_check(string[0]))
        return (0);
    while (string[i])
    {
        if (other_letters_check(string[i]))
            return (0);
        i++;
    }
    return (1);
}

int determine_quote_type(char letter, int quote_type)
{
    if (quote_type == SINGLE_QUOTE && letter == SINGLE_QUOTE)
        quote_type = 0;
    else if (quote_type == DOUBLE_QUOTE && letter == DOUBLE_QUOTE)
        quote_type = 0;
    else if (quote_type == 0 && letter == SINGLE_QUOTE)
        quote_type = SINGLE_QUOTE;
    else if (quote_type == 0 && letter == DOUBLE_QUOTE)
        quote_type = DOUBLE_QUOTE;
    return (quote_type);
}

int count_valid_char(char *quoted_word)
{
    int i;
    int counter;
    int quote_type;
    
    quote_type = 0;
    counter = 0;
    i = 0;
    while (quoted_word[i])
    {
        if (quote_type != 0)
        {
            if ((quote_type = determine_quote_type(quoted_word[i], quote_type)) == 0)
                i++;
        }
        else
            quote_type = determine_quote_type(quoted_word[i], quote_type);
        if (quoted_word[i] != quote_type)
            counter++;
        i++;
    }
    return (counter);
}

int get_real_quote_type(char letter, int quote_type, int *i)
{
    if (quote_type != 0)
    {
        if ((quote_type = determine_quote_type(letter, quote_type)) == 0)
            (*i)++;
    }
    else
        quote_type = determine_quote_type(letter, quote_type);
    return (quote_type);
}

char    *get_rid_of_quotes(char *word)
{
    int     i;
    int     quote_type;
    char    *new_word;
    int     local_index;
    
    i = 0;
    quote_type = 0;
    new_word = malloc(sizeof(char) * (count_valid_char(word) + 1));
    if (!new_word)
        return (NULL);
    while (word[i])
    {
        quote_type = get_real_quote_type(word[i], quote_type, &i);
        if (word[i] != quote_type)
            new_word[local_index++] = word[i++];
        else
            i++;
    }
    word[i] = 0;
    return (word);
}

int minishell(const char *read_line)
{
    int i;
    t_token *tokens;
    char    **split_line;
    
    i = 0;
    split_line = split(read_line);
    tokens = malloc(sizeof(t_token) * word_counter(read_line));
    create_structs(tokens, split_line);
    while (split_line[i])
    {
        printf("type: %i, value: %s\n", tokens[i].type, tokens[i].value);
        i++;
    }
    return (0);
}

int main(void)
{
    minishell("ls | cat >> 'hello' > okcso");
    return (0);
}