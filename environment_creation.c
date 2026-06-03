/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:41:39 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/06/03 12:40:36 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     number_of_env_variables(t_token *tokens)
{
    int i;
    int env_variables;

    i = 0;
    while (tokens[i].value != NULL)
    {
        if (tokens[i].type == token_env_assign)
            env_variables++;
        i++;
    }
    return (env_variables);
}

int     key_counter(const char *envp)
{
    int i;

    i = 0;
    while (envp[i] != EQUAL_SIGN)
        i++;
    return (i);
}

int     value_counter(const char *envp)
{
    int i;
    int final;
    
    i = 0;
    while (envp[i] != EQUAL_SIGN)
        i++;
    i++;
    final = i;
    while (envp[i])
        i++;
    return (i - final);
    
}

t_envs  copy_from_token_list(t_token tokens)
{
    t_envs new_node;
    int i;
    int j;

    i = 0;
    j = 0;
    new_node.key = malloc(sizeof(char) * (key_counter(tokens.value) + 1));
    new_node.value = malloc(sizeof(char) * (value_counter(tokens.value)) + 1);
    while (tokens.value[i] != EQUAL_SIGN)
        new_node.key[j++] = tokens.value[i++];
    new_node.key[j] = 0;
    i++;
    j = 0;
    while (tokens.value[i])
        new_node.value[j++] = tokens.value[i++];
    new_node.value[j] = 0;
    return (new_node);
}

void    fill_up_env_list(t_envs *env_list, t_token *tokens)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (tokens[j].value != NULL)
    {
        if (tokens[j].type == token_env_assign)
            env_list[i++] = copy_from_token_list(tokens[j++]);
        else
            j++;
    }
    env_list[i].key = NULL;
    env_list[i].value = NULL;
}

t_envs    *env_list_creation(t_token *tokens)
{
    t_envs *env_list;
    
    env_list = malloc(sizeof(t_envs) * (number_of_env_variables(tokens) + 1));
    if (!env_list)
        return (NULL);
    fill_up_env_list(env_list, tokens);
    return (env_list);
}