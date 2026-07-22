/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/07/22 20:30:33 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "env_assign_helpers.c"
// #include "rest_helpers.c"
// #include "split_helpers.c"
// #include "split.c"
// #include "stepping_in_input.c"
// #include "syntax_error_check.c"
// #include "expansion_check.c"
// #include "environment_creation.c"
// #include "skippers.c"
// #include "tokenizing.c"
// #include "env_assign.c"
// #include "dollar_sign_handler.c"
// #include "is_special_character.c"
// #include "special_characters_checkers.c"
// #include "word_count_helpers.c"

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
        get_real_quote_type(quoted_word, &quote_type, &i);
        if (quoted_word[i] != quote_type)
        {
            counter++;
            i++;
        }
    }
    return (counter);
}

void get_real_quote_type(char *word, int *quote_type, int *i)
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

char    *get_rid_of_quotes(char *word, t_token token)
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
        get_real_quote_type(word, &quote_type, &i);
        if (is_dollar_sign(word[i]))
            token.quote_type = quote_type;
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
                split_line[i] = get_rid_of_quotes(split_line[i], tokens[i]);
                tokens[i].value = split_line[i];
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

t_token *minishell(const char *read_line, t_envs *env_list)
{
    // int     i;
    t_token *tokens;
    char    **split_line;
    char    **converted;

    // i = 0;
    if(*read_line == '\0')
   		return (NULL);
    split_line = split_read_line(read_line);
    // printf("%i\n", word_counter(read_line));
    tokens = malloc(sizeof(t_token) * (word_counter(read_line) + 1));
    create_token_struct(tokens, split_line);
    env_list = env_list_addition(tokens, env_list);
    remove_quoted_word(split_line, tokens);
    // printf("GECI\n");
    handle_expansions(env_list, tokens);
    // while (split_line[i])
    // {
    //     printf("type: %i, value: %s, quote_type: %i\n", tokens[i].type, tokens[i].value, tokens[i].quote_type);
    //     i++;
    // }
    if (syntax_check(tokens))
        return (NULL);
    converted = convert_struct_to_double_string(tokens);
    (void) converted;
    return (tokens);
}

// int main()
// {
//     char    **okcso;
//     t_envs  *global_env_list;

//     global_env_list = NULL;
//     okcso = minishell("okcso $here", global_env_list);
//     if (!okcso)
//         return (1);
//     return (0);
// }
/* void print_cmds(t_cmds *head)
{
	t_cmds *curr = head;
	int node = 1;
	while (curr)
	{
		printf("--- Node %d ---\n", node);
		printf("fd_in: %d, fd_out: %d\n", curr->fd_in, curr->fd_out);
		int i = -1;
		while (curr->cmd && curr->cmd[++i])
			printf("arg[%d]: %s\n", i, curr->cmd[i]);
		node++;
		curr = curr->next;
	}
} */
int main(int ac, char **av, char **envp)
{
	char *line;
	t_envs  *global_env_list;
	t_token *tokens;
	t_cmds *cmds;
	(void)ac;
	(void)av;

	global_env_list = NULL;
	cmds = NULL;
	while ((line = readline("minishell$ ")))
	{
		tokens = minishell(line, global_env_list);//free on fail
		if (!tokens)
			continue;
		cmds = build_cmds(tokens);//free on fail
		execute_cmds(cmds, envp);
		if (line[0] != '\0' || !line)
			add_history(line);
	}
    return (0);
}
