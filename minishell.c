/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/08/27 13:28:33 by guthybarnak      ###   ########.fr       */
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

int     count_valid_char(const char *quoted_word)
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

void    get_real_quote_type(const char *word, int *quote_type, int *i)
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
    free((void*)tokens[i].value);
    return (new_word);
}

void    remove_quotes(t_token *tokens)
{
    int i;
    int j;

    i = 1;
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

void    copy_key(const char *envp, char *new_key)
{
    int i;

    i = 0;
    while (envp[i] != EQUAL_SIGN)
    {
        new_key[i] = envp[i];
        i++;
    }
}

char    *insert_key(const char *envp)
{
    char    *new_key;
    
    new_key = malloc(sizeof(char) * (key_counter(envp) + 1));
    if (!new_key)
        return (NULL);
    copy_key(envp, new_key);
    return (new_key);   
}

void    copy_value(const char *envp, char *new_value)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (envp[i] != EQUAL_SIGN)
        i++;
    i++;
    while (envp[i])
        new_value[j++] = envp[i++];
}

char    *insert_value(const char *envp)
{
    char    *new_value;

    new_value = malloc(sizeof(char) * (value_counter(envp) + 1));
    if (!new_value)
        return (NULL);
    copy_value(envp, new_value);
    return (new_value);
}

int     clean_up_env_list(t_envs *env_list, int i)
{
    int j;

    j = 0;
    while (j <= i)
    {
        free(env_list[j].key);
        free(env_list[j].value);
        j++;
    }
    free(env_list);
    return (0);
}

int    copy_from_envp_to_own_env_list(const char **envp, t_envs *env_list)
{
    int i;

    i = 0;
    while (envp[i])
    {
        env_list[i].key = insert_key(envp[i]);
        if (!env_list[i].key)
            return (clean_up_env_list(env_list, i));
        env_list[i].value = insert_value(envp[i]);
        if (!env_list[i].value)
            return (clean_up_env_list(env_list, i));
        i++;
    }
    env_list[i].key = NULL;
    env_list[i].value = NULL;
    return (1);
}

int     get_len_of_envp(const char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return (i);
}

int     put_envp_into_own_env_list(const char **envp, t_envs *env_list)
{
    int list_size;

    list_size = get_len_of_envp(envp);
    env_list = malloc(sizeof(t_envs) * (list_size + 1));
    if (!env_list)
        return (0);
    if (!copy_from_envp_to_own_env_list(envp, env_list))
        return (0);
    return (1);
}

t_token    *minishell(const char *read_line, t_envs *env_list)
{
    int     i;
    t_token *tokens;
    char    **split_line;

    i = 0;
    split_line = split_read_line(read_line);
    printf("%i\n", word_counter(read_line));
    tokens = malloc(sizeof(t_token) * (word_counter(read_line) + 2));
    create_token_struct(tokens, split_line);
    env_list = env_list_addition(tokens, env_list);
    handle_expansions(env_list, tokens);
    remove_quotes(tokens);
    while (split_line[i])
    {
        printf("type: %i, value: %s\n", tokens[i + 1].type, tokens[i + 1].value);
        i++;
    }
    if (syntax_check(tokens))
        return (NULL);
    return (tokens);
}

int main(int args, char **argv, const char **envp)
{
    t_token    *okcso;
    t_envs  *global_env_list;

    global_env_list = NULL;
    if (!put_envp_into_own_env_list(envp, global_env_list))
        return (1);
    okcso = minishell("$$$?", global_env_list);
    if (!okcso)
        return (1);
    return (0);
}