/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:41:39 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/05/28 15:25:02 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int     number_of_env_variables(char **envp, t_token *tokens)
{
    int i;
    int env_variables;

    i = 0;
    while (envp[i])
        i++;
    env_variables = i;
    i = 0;
    while (tokens[i].value != NULL)
    {
        if (tokens[i].type == token_env_assign)
            env_variables++;
        i++;
    }
    return (env_variables);
}

t_envs  *copy_from_env(char *envp)
{
    int i;
    int j;
    t_envs *new_node;
    
    i = 0;
    j = 0;
    new_node = malloc(sizeof(t_envs));
    printf("key: %p\n", new_node->key);
    while (envp[i] != EQUAL_SIGN)
        new_node->key[j++] = envp[i++];
    i++;
    new_node->key[j] = 0;
    j = 0;
    printf("value: %p\n", new_node->value);
    while (envp[i])
        new_node->value[j++] = envp[i++];
    new_node->value[j] = 0;
    return (new_node);
}

t_envs  *copy_from_token_list(t_token tokens)
{
    t_envs *new_node;
    int i;
    int j;

    i = 0;
    j = 0;
    new_node = malloc(sizeof(t_envs));
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

void    fill_up_env_list(t_envs **env_list, char **envp, t_token *tokens)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*envp[i])
    {
        env_list[i] = copy_from_env(envp[i]);
        i++;
    }
    while (tokens[j].value != NULL)
    {
        if (tokens[j].type == token_env_assign)
            env_list[i++] = copy_from_token_list(tokens[j++]);
        else
            j++;
    }
    env_list[i]->key = NULL;
    env_list[i]->value = NULL;
}

t_envs    **env_list_creation(t_token *tokens, char **envp)
{
    t_envs **env_list;
    
    env_list = malloc(sizeof(t_envs *) * (number_of_env_variables(envp, tokens) + 1));
    if (!env_list)
        return (NULL);
    fill_up_env_list(env_list, envp, tokens);
    return (env_list);
}