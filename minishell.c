/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:02:10 by bguhty            #+#    #+#             */
/*   Updated: 2026/07/13 18:08:16 by dabdulla         ###   ########.fr       */
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

char    **minishell(const char *read_line, t_envs *env_list)
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
    return (converted);
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

int main()
{
	char *path;
	char *str;
	char **av;
	char  *tmp;
	extern char **environ;
	t_envs  *global_env_list;

	pid_t pid;
	path = "/Users/dorianabdullahi/.local/bin:/Users/dorianabdullahi/miniforge3/bin:/opt/homebrew/bin:/Users/dorianabdullahi/.local/share/solana/install/active_release/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks/Python.framework/Versions/3.10/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/pkg/env/global/bin:/opt/X11/bin:/Library/Apple/usr/bin:/usr/local/share/dotnet:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Users/dorianabdullahi/.gem/bin:/Users/dorianabdullahi/flutter/flutter/bin:/Users/dorianabdullahi/.local/bin:/Users/dorianabdullahi/miniforge3/bin:/Users/dorianabdullahi/.local/share/solana/install/active_release/bin:/Users/dorianabdullahi/.cargo/bin:/Users/dorianabdullahi/.pub-cache/bin:/Applications/Docker.app/Contents/Resources/bin/:/Users/dorianabdullahi/Desktop/development/sdks/flutter/bin:/Applications/Docker.app/Contents/Resources/bin/:/Users/dorianabdullahi/Desktop/development/sdks/flutter/bin";
	global_env_list = NULL;
	while ((str = readline("minishell: ")))
	{
		av = minishell(str, global_env_list);
		if (!av)
			continue;
		// printf("%s\n, %s\n",av[0], av[1]);
		// path = av[0];
		// int i = 0;
		// while (av[i])
		// {
		// 	printf("%s\n", av[i]);
		// 	i++;
		// }
		// return 0;
		tmp = handling_path(av[0], path);
		if (!tmp)
			continue;
		pid = fork();
		if (pid == 0)
		{
			execve(tmp, av, environ);
			perror("execve");
			exit(1);
		}
		waitpid(pid, NULL, 0);
		//free arguments of av
	}
	if (!path)
		return 0;
    // if (minishell("lofasz$$$festek"))
    //     return (1);
    return (0);
}
