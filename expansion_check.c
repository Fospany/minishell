/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:53:31 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/05/28 15:21:10 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_if_in_env_list(t_envs **env_list, char *expandable)
{
    int i;
    
    i = 0;
    while (env_list[i]->key != NULL)
    {
        if (string_compare(env_list[i]->key, expandable))
            return (1);
        i++;
    }
    return (0);
}

char    *copy_from_env_list(t_envs **env_list, char *expandable)
{
    int i;
    
    i = 0;
    while (env_list[i]->key != NULL)
    {
        if (string_compare(env_list[i]->key, expandable))
        {
            free(expandable);
            return (env_list[i]->value);
        }
        i++;
    }
    return (NULL);
}

void    check_for_expansion_and_replace(t_envs **env_list, t_token *tokens)
{
    int i;
    
    i = 0;
    while (tokens[i].value)
    {
        if (is_dollar_sign(tokens[i].value[0]))
        {
            if (check_if_in_env_list(env_list, tokens[i].value))
                tokens[i].value = copy_from_env_list(env_list, tokens[i].value);
            else
                tokens[i].value = getenv(tokens[i].value);
        }
        i++;
    }
}