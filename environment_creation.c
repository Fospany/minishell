/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:41:39 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/08/26 11:52:47 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     number_of_env_variables(t_token *tokens, t_envs *env_list)
{
    int i;
    int env_variables;

    i = 0;
    env_variables = 0;
    while (tokens[i].value != NULL)
    {
        if (tokens[i].type == token_env_assign)
            env_variables++;
        i++;
    }
    i = 0;
    if (!env_list)
        return (env_variables);
    while (env_list[i].key)
    {
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

void    fill_up_env_list(t_envs *new_env_list, t_token *tokens, t_envs *prev_env_list)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (prev_env_list && prev_env_list[i].key)
    {
        new_env_list[i].key = prev_env_list[i].key;
        new_env_list[i].value = prev_env_list[i].value;
        i++;
    }
    while (tokens[j].value != NULL)
    {
        if (tokens[j].type == token_env_assign)
            new_env_list[i++] = copy_from_token_list(tokens[j++]);
        else
            j++;
    }
    new_env_list[i].key = NULL;
    new_env_list[i].value = NULL;
}

t_envs    *env_list_addition(t_token *tokens, t_envs *env_list)
{
    t_envs *new_full_env_list;

    new_full_env_list = malloc(sizeof(t_envs) * (number_of_env_variables(tokens, env_list) + 1));
    if (!new_full_env_list)
        return (NULL);
    fill_up_env_list(new_full_env_list, tokens, env_list);
    return (env_list);
}
