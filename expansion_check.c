/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguthy <bguthy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:53:31 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/05/28 18:44:57 by bguthy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_multiple_dollar_signs(char *word)
{
    int i;
    int dollar_signs;

    dollar_signs = 0;
    i = 0;
    while (word[i])
    {
        if (word[i] == DOLLAR_SIGN)
            dollar_signs++;
        i++;
    }
    if (dollar_signs > 1)
        return (1);
    else
        return (0);
}

int     check_if_in_env_list(t_envs *env_list, char *expandable)
{
    int i;
    
    i = 0;
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, expandable))
            return (1);
        i++;
    }
    return (0);
}

char    *copy_from_env_list(t_envs *env_list, char *expandable)
{
    int i;
    
    i = 0;
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, expandable + 1))
        {
            free(expandable);
            return (env_list[i].value);
        }
        i++;
    }
    free(expandable);
    return (NULL);
}

int     skip_to_next_dollar_sign(char *expandable, int counter)
{
    int dollar_signs;
    int i;

    i = 0;
    dollar_signs = 0;
    while (expandable[i])
    {
        if (is_dollar_sign(expandable[i]))
            dollar_signs++;
        if (dollar_signs == counter + 1)
            return (i);
    }
    return (i);
}

int     ft_strlen(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (i);
    while (s[i])
        i++;
    return (i);
}

int     number_of_dollar_signs(char *expandable)
{
    int i;
    int dollar_signs;

    i = 0;
    dollar_signs = 0;
    while (expandable[i])
    {
        if (is_dollar_sign(expandable[i]))
            dollar_signs++;
        i++;
    }
    return (dollar_signs);
}

char    *allocation_for_expanded_word(t_envs *env_list, char *expandable, int dollar_signs)
{
    int i;
    int full_len;
    int counter;
    char *new_word;

    counter = 0;
    full_len = 0;
    new_word = NULL;
    i = 0;
    while (env_list[i].value)
    {
        if (counter == dollar_signs)
            break ;
        if (string_compare(env_list[i].key, expandable))
        {
            full_len += ft_strlen(env_list[i].value);
            counter ++;
        }
        i++;
    }
    new_word = malloc(sizeof(char) * (full_len + 1));
    return (new_word);
}

char    *expand_variables(char *expandable, t_envs *env_list, int expanded_flag, char *new_word)
{
    int i;
    int new_start;

    i = 0;
    while (expandable[i])
    {
        if (is_dollar_sign(expandable[i]))
        {
            if (check_multiple_dollar_signs(expandable))
                expand_variables(expandable  + new_start, env_list, expanded_flag + 1, new_word);
            if (expanded_flag > 0)
                new_start = skip_to_next_dollar_sign(expandable, expanded_flag);
            if (check_if_in_env_list(env_list, expandable + new_start))
                new_word = copy_from_env_list(env_list, expandable + new_start);
            else
                new_word = getenv(expandable + 1);
        }
    }
    return (NULL);
}

void    check_for_expansion_and_replace(t_envs *env_list, t_token *tokens)
{
    int i;
    int dollar_signs;
    char    *fully_expanded_string;
    
    i = 0;
    while (tokens[i].value)
    {
        dollar_signs = number_of_dollar_signs(tokens[i].value);
        fully_expanded_string =  allocation_for_expanded_word(env_list, tokens[i].value, dollar_signs);
        expand_variables(tokens[i].value, env_list, 0, fully_expanded_string);
        i++;
    }
}
