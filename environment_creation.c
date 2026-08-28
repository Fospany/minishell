/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:41:39 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/08/28 18:06:34 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     number_of_env_variables(t_token *token)
{
    int env_variables;
    int i;

    i = 0;
    env_variables = 0;
    while (token[i].value)
    {
        if (token[i].type == token_env_assign)
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
t_envs  *copy_from_token_list(t_token tokens)
{
    t_envs *new_node;
    int j;
    int i;
    
    i = 1;
    j = 0;
    new_node = malloc(sizeof(t_envs));
    new_node->key = malloc(sizeof(char) * (key_counter(tokens.value) + 1));
    if (!new_node->key)
        return (NULL);
    new_node->value = malloc(sizeof(char) * (value_counter(tokens.value)) + 1);
    if (!new_node->value)
        return (free(new_node->key), NULL);
    new_node->next = NULL;
    while (tokens.value[i] != EQUAL_SIGN)
        new_node->key[j++] = tokens.value[i++];
    new_node->key[j] = 0;
    i++;
    j = 0;
    while (tokens.value[i])
        new_node->value[j++] = tokens.value[i++];
    new_node->value[j] = 0;
    return (new_node);
}

int     add_env_variables_to_env_list(t_envs *env_list, t_token *tokens)
{
    t_envs  *new_node;
    int     i;

    i = 0;
    while (tokens[i].value)
    {
        if (tokens[i].type == token_env_assign)
        {
            new_node = copy_from_token_list(tokens[i]);
            if (!new_node)
                return (0);
            else
                ft_lstadd_back(&env_list, new_node);
        }
        i++;
    }
    return (1);
}
