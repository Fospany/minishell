/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/27 08:46:42 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_assign_helpers.c"
#include "rest_helpers.c"
#include "split_helpers.c"
#include "split.c"
#include "stepping_in_input.c"
#include "syntax_error_check.c"
#include <string.h>


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
    tokens[i].value = NULL;
    tokens[i].type = -1;
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
        if (!other_letters_check(string[i]))
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
        get_real_quote_type(quoted_word, quote_type, &i);
        if (quoted_word[i] != quote_type)
        {
            counter++;
            i++;
        }
    }
    return (counter);
}

int get_real_quote_type(char *word, int quote_type, int *i)
{
    while (check_for_quote(word[*i], &quote_type) && word[*i] == word[(*i) + 1])
        (*i)++;
    if (!check_for_quote(word[*i], &quote_type))
        return (quote_type);
    if (quote_type != 0)
    {
        if ((quote_type = determine_quote_type(word[*i], quote_type)) == 0)
            (*i)++;
    }
    else
    {
        quote_type = determine_quote_type(word[*i], quote_type);
        (*i)++;
    }
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
    local_index = 0;
    new_word = malloc(sizeof(char) * (count_valid_char(word)) + 1);
    if (!new_word)
        return (NULL);
    while (word[i])
    {
        quote_type = get_real_quote_type(word, quote_type, &i);
        if (word[i] != quote_type && word[i])
        {
            new_word[local_index++] = word[i++];
        }
        else if (word[i])
            i++;
    }
    new_word[local_index] = 0;
    free(word);
    return (new_word);
}

void    remove_quoted_word(char **split_line, t_token *tokens)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (split_line[i])
    {
        while (split_line[i][j])
        {
            if (check_for_quote_without_quote_type(split_line[i][j]))
            {
                split_line[i] = get_rid_of_quotes(split_line[i]);
                tokens[i].value = split_line[i];
                break ;
            }
            j++;
        }
        i++;
        j = 0;
    }
}

int minishell(const char *read_line, char **envp)
{
    int     i;
    t_token *tokens;
    t_envs  *my_env_list;
    char    **split_line;
    
    i = 0;
    split_line = split(read_line);
    printf("%i\n", word_counter(read_line));
    tokens = malloc(sizeof(t_token) * (word_counter(read_line) + 1));
    create_structs(tokens, split_line);
    remove_quoted_word(split_line, tokens);
    while (split_line[i])
    {
        printf("type: %i, value: %s\n", tokens[i].type, tokens[i].value);
        i++;
    }   
    if (syntax_check(tokens))
        return (1);
    free(tokens);
    free(split_line);
    return (0);
}

int main(int args, char **argv, char **envp)
{
    if (minishell("$cat", envp))
        return (1);
    return (0);
}