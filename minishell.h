/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguthy <bguthy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:20:37 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/28 17:27:39 by bguthy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define a 97
# define A 65
# define z 122
# define Z 90
# define SPACE 32
# define HORIZONTAL_TAB 9
# define CARRIAGE_RET 13
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define EQUAL_SIGN 61
# define DOLLAR_SIGN 36
# define REDIR_IN 60
# define REDIR_OUT 62
# define PIPE 124


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef enum e_token_type
{
    token_word,
    token_pipe,
    token_redirect_in,
    token_redirect_out,
    token_append,
    token_heredoc,
    token_env_assign
}   t_token_type;

typedef struct s_envs
{
    char            *key;
    char            *value;
}                   t_envs;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
}                   t_token;

int     string_compare(char *string1, char *string2);
int     other_letters_check(char c);
int     first_letter_check(char letter);
int     is_number(char letter);
int     is_upper_case(char letter);
int     is_lower_case(char letter);
void	fill_up_double_pointer(char **split_line, const char *read_line);
char	**split(const char *read_line);
char	**allocating_double_pointer(const char *read_line);
int		count_letters(const char *read_line, int i);
int		word_counter(const char *read_line);
int		is_word_2(const char *read_line, int *i, int *words);
int		check_for_quote(const char letter, int *quote_type);
void    skip_white_spaces(const char *read_line, int *i);
int		is_white_space(const char letter);
void	skip_to_next_quote(const char *read_line, int *i, char quote_type);
void    skip_non_white_spaces(const char *read_line, int *i);
void    split_clean_up(char **split_line, int i);
int     env_assign_check(char *string);
void    remove_quoted_word(char **split_line, t_token *tokens);
int     check_for_quote_without_quote_type(const char letter);
int     get_real_quote_type(char *word, int quote_type, int *i);
t_envs  *env_list_creation(t_token *tokens, char **envp);
int     dollar_sign_exception(const char *read_line, int *i, int *words);
int     is_heredoc_or_append(const char letter1, const char letter2);
int     is_special_character(const char *read_line, int i, int *letters);
int     is_redir_or_pipe(const char letter);
int     quote_in_word(const char *read_line, int *i, int *words);
int     syntax_error_message_display(char *token_value);
int     is_dollar_sign(const char letter);
int     is_pipe(const char letter);
void    check_for_expansion_and_replace(t_envs *env_list, t_token *tokens);
int     syntax_check(t_token *tokens);


#endif