/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/08/25 17:38:36 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_assign_helpers.c"
#include "rest_helpers.c"
#include "split_helpers.c"
#include "split.c"
#include "stepping_in_input.c"
#include "syntax_error_check.c"
#include "expansion_check.c"
#include "environment_creation.c"
#include "skippers.c"
#include "tokenizing.c"
#include "env_assign.c"
#include "dollar_sign_handler.c"
#include "is_special_character.c"
#include "special_characters_checkers.c"
#include "word_count_helpers.c"

int     determine_quote_type(char letter, int quote_type)
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

int     count_valid_char(char *quoted_word)
{
    int i;
    int counter;
    int quote_type;

    quote_type = 0;
    counter = 0;
    i = 0;
    while (quoted_word[i])
    {
        get_real_quote_type(quoted_word, &quote_type, &i);
        if (quoted_word[i] != quote_type)
        {
            counter++;
            i++;
        }
    }
    return (counter);
}

void    get_real_quote_type(char *word, int *quote_type, int *i)
{
    while (check_for_quote(word[*i], quote_type) && word[*i] == word[(*i) + 1])
        (*i)++;
    if (!check_for_quote(word[*i], quote_type))
        return ;
    if (*quote_type != 0)
    {
        if ((*quote_type = determine_quote_type(word[*i], *quote_type)) == 0)
            (*i)++;
    }
    else
    {
        *quote_type = determine_quote_type(word[*i], *quote_type);
        (*i)++;
    }
}

char    *get_rid_of_them_quotes(t_token *tokens, int i)
{
    int     j;
    int     quote_type;
    int     local_index;
    char    *new_word;
    
    quote_type = 0;
    j = 0;
    local_index = 0;
    new_word = malloc(sizeof(char) * (count_valid_char(tokens[i].value) + 1));
    if (!new_word)
        return (NULL);
    while (tokens[i].value[j])
    {
        get_real_quote_type(tokens[i].value, &quote_type, &j);
        if (tokens[i].value[j] != quote_type && tokens[i].value[j])
            new_word[local_index++] = tokens[i].value[j++];
        else if (tokens[i].value[j])
            j++;
    }
    new_word[local_index] = 0;
    free(tokens[i].value);
    return (new_word);
}

void    remove_quotes(t_token *tokens)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tokens[i].value)
    {
        while (tokens[i].value[j])
        {
            if (check_for_quote_without_quote_type(tokens[i].value[j]))
            {
                tokens[i].value = get_rid_of_them_quotes(tokens, i);
                break ;
            }
            j++;
        }
        i++;
        j = 0;
    }
    
    
}

int     number_of_valid_tokens(t_token *tokens)
{
    int i;
    int valid_tokens;

    valid_tokens = 0;
    i = 0;
    while (tokens[i].value)
    {
        if (tokens[i].type != 6)
            valid_tokens++;
        i++;
    }
    return (valid_tokens);
}

char    **convert_struct_to_double_string(t_token *tokens)
{
    int     i;
    int     words;
    char    **converted;

    i = 0;
    words = 0;
    converted = malloc(sizeof(char *) * (number_of_valid_tokens(tokens) + 1));
    while (tokens[i].value)
    {
        if (tokens[i].type != 6)
            converted[words++] = tokens[i].value;
        i++;
    }
    converted[words] = NULL;
    return (converted);
}
char    **minishell(const char *read_line, t_envs *env_list)
{
    int     i;
    t_token *tokens;
    char    **split_line;
    char    **converted;

    i = 0;
    split_line = split_read_line(read_line);
    printf("%i\n", word_counter(read_line));
    tokens = malloc(sizeof(t_token) * (word_counter(read_line) + 1));
    create_token_struct(tokens, split_line);
    env_list = env_list_addition(tokens, env_list);
    handle_expansions(env_list, tokens);
    remove_quotes(tokens);
    while (split_line[i])
    {
        printf("type: %i, value: %s\n", tokens[i].type, tokens[i].value);
        i++;
    }
    if (syntax_check(tokens))
        return (NULL);
    converted = convert_struct_to_double_string(tokens);
    return (converted);
}

int main()
{
    char    **okcso;
    t_envs  *global_env_list;

    global_env_list = NULL;
    okcso = minishell("'$T'E$R'M'", global_env_list);
    if (!okcso)
        return (1);
    return (0);
}