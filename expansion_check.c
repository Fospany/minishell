/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:53:31 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/06/23 13:19:03 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    copy_till_next_dollar(char *dest, char *source)
{
    int i;

    i = 0;
    while (source[i] && !is_dollar_sign(source[i]))
    {
        if (check_for_quote_without_quote_type(source[i]))
            break ;
        dest[i] = source[i];
        i++;
    }
    dest[i] = 0;
}

int     dollar_in_word(char *word)
{
    int i;

    i = 0;
    while (word[i])
    {
        if (is_dollar_sign(word[i]))
            return (1);
        i++;
    }
    return (0);
}

char    *create_mock_word(char *expandable)
{
    char    *mock_word;
    
    mock_word = malloc(sizeof(char) * (count_letters_in_expansion(expandable + 1) + 1));
    if (!mock_word)
        return (NULL);
    copy_till_next_dollar(mock_word, expandable + 1);
    return (mock_word);
}

int     check_if_in_my_env_list(t_envs *env_list, char *expandable)
{
    int i;
    char    *new_word;

    new_word = malloc(sizeof(char) * (skip_to_next_dollar_sign(expandable) + 1));
    copy_till_next_dollar(new_word, expandable);
    i = 0;
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, new_word))
            return (1);
        i++;
    }
    return (0);
}

int     get_length_of_expansion(t_envs *env_list, char *expandable)
{
    int i;

    i = 0;
    while (env_list[i].value)
    {
        if (string_compare(env_list[i].key, expandable))
            return (ft_strlen(env_list[i].value));
        i++;
    }
    return (0);
}

int     count_letters_till_next_quote(const char *word, int *i)
{
    int letters;
    int quote_type;

    quote_type = word[*i];
    letters = 2;
    (*i)++;
    while (word[*i])
    {
        if (word[*i] == quote_type)
        {
            (*i)++;
            return (letters);
        }
        letters++;
        (*i)++;
    }
    return (letters);
}

int     get_full_len_of_expandable(char *expandable, t_envs *env_list)
{
    char    *mock_word;
    int     i;
    int     len;
    int     quote_type;

    quote_type = 0;
    i = 0;
    len = 0;
    while (expandable[i])
    {
        mock_word = create_mock_word(expandable + i);
        i += ft_strlen(mock_word);
        len += get_length_of_expansion(env_list, mock_word);
        if (check_for_quote(expandable[i], &quote_type))
            len += count_letters_till_next_quote(expandable, &i);
        i++;
    }
    return (len);
}

int     invalid_for_after_dollar(const char letter)
{
    if (letter == DOLLAR_SIGN)
        return (1);
    else if (check_for_quote_without_quote_type(letter))
        return (1);
    else
        return (0);
}

int     count_letters_in_expansion(char *expandable)
{
    int i;

    i = 0;
    while (expandable[i])
    {
        if (invalid_for_after_dollar(expandable[i]))
            return (i);
        i++;
    }
    return (i);
}

int    copy_from_env_list(t_envs *env_list, char *expandable, char *fully_expanded, int *index)
{
    int i;
    int j;
    char    *new_word;

    i = 0;
    j = 0;
    new_word = malloc(sizeof(char) * (skip_to_next_dollar_sign(expandable) + 1));
    copy_till_next_dollar(new_word, expandable);
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, new_word))
        {
            while (env_list[i].value[j])
                fully_expanded[(*index)++] = env_list[i].value[j++];
            return (ft_strlen(new_word));
        }
        i++;
    }
    return (j);
}

int     copy_until_next_quote(const char *expandable, char *fully_expanded, int *index, int *quote_type)
{
    int i;

    i = 0;
    while (expandable[i])
    {
        if (check_for_quote(expandable[i], quote_type))
            return (i);
        else
            fully_expanded[(*index)++] = expandable[i++];
    }
    return (i);
}

int     digit_counter(pid_t pid)
{
    int digits;

    digits = 0;
    while (pid > 0)
    {
        pid /= 10;
        digits++;
    }
    return (digits);
}

char    *my_itoa(pid_t pid)
{
    int     digits;
    char    *pid_string;

    pid = (int)pid;
    digits = digit_counter(pid);
    pid_string = malloc(sizeof(char) * (digits + 1));
    pid_string[digits] = 0;
    while (pid > 0)
    {
        pid_string[--digits] = pid % 10 + '0';
        pid /= 10;
    }
    return (pid_string);
}

void    handle_double_dollars(char *fully_expanded, int *index)
{
    char    *pid;
    int     i;

    i = 0;
    pid = my_itoa(getpid());
    while (pid[i])
        fully_expanded[(*index)++] = pid[i++];
}

int     check_in_real_environment_list(char *expandable)
{
    if (getenv(expandable))
        return (1);
    return (0);
}

void    copy_from_real_environment_list(char *expandable, char *fully_expanded, int *index)
{
    char    *test_env;
    int     len;
    int     counter;
    
    counter = 0;
    test_env = getenv(expandable);
    len = ft_strlen(test_env);
}

char    *create_the_whole_word(char *expandable, t_envs *env_list, int token_type)
{
    int     i;
    int     j;
    int     quote_type;
    char    *fully_expanded;

    fully_expanded = malloc(sizeof(char) * (get_full_len_of_expandable(expandable, env_list) + 2));
    quote_type = 0;
    i = 0;
    j = 0;
    while (expandable[i])
    {
        if (is_dollar_sign(expandable[i]))
        {
            if (is_dollar_after_dollar(expandable[i + 1]))
            {
                handle_double_dollars(fully_expanded, &j);
                i += 2;
            }
            else if (check_if_in_my_env_list(env_list, expandable + i))
                i += copy_from_env_list(env_list, expandable  + i, fully_expanded, &j);
            else if (check_in_real_environment_list(expandable + i))
            {
                copy_from_real_environment_list(expandable + i, fully_expanded, &j);
            }
            else
            {
                fully_expanded[j] = 0;
                return (fully_expanded);
            }
        }
        else if (check_for_quote(expandable[i], &quote_type))
        {
            i++;
            i += copy_until_next_quote(expandable + i, fully_expanded, &j, &quote_type);
        }
        else
            fully_expanded[j++] = expandable[i++];
    }
    fully_expanded[j] = 0;
    return (fully_expanded);
}

char    *copy_till_equal_sign(char *expandable)
{
    int     i;
    char    *new_key;

    i = 0;
    new_key = malloc(sizeof(char) * (key_counter(expandable) + 1));
    while (expandable[i] != EQUAL_SIGN)
    {
        new_key[i] = expandable[i];
        i++;
    }
    new_key[i] = 0;
    return (new_key);
}

char    *copy_for_env_assign(char *env_assign_value)
{
    char    *new_word;
    int     i;
    
    i = 0;
    new_word = malloc(sizeof(char) * (ft_strlen(env_assign_value) + 1));
    while (env_assign_value[i])
    {
        new_word[i] = env_assign_value[i];
        i++;
    }
    new_word[i] = 0;
    return (new_word);
}

char    *expand_env_assign(char *expandable, t_envs *env_list, int *index)
{
    char    *new_key;
    char    *new_word;
    int     i;
    
    i = 0;
    new_key = copy_till_equal_sign(expandable);
    while (!string_compare(new_key, env_list[i].key))
        i++;
    new_word = copy_for_env_assign(env_list[i].value);
    (*index) += ft_strlen(new_word);
    return (new_word);
}

void    handle_expansions(t_envs *env_list, t_token *tokens)
{
    int i;

    i = 0;
    while (tokens[i].value)
    {
        if (dollar_in_word(tokens[i].value))
            tokens[i].value = create_the_whole_word(tokens[i].value, env_list, tokens[i].type);
        i++;
    }
}
