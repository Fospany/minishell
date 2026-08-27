/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:20:37 by bguhty            #+#    #+#             */
/*   Updated: 2026/08/27 17:10:41 by guthybarnak      ###   ########.fr       */
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
# define QUESTION_MARK 63


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include "libft/libft.h"


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
    char                *key;
    char                *value;
    struct s_envs       *next;
}                       t_envs;

typedef struct s_token
{
    const char            *value;
    t_token_type    type;
}                   t_token;

void    *ft_calloc(size_t nmemb, size_t size);
int     string_compare(const char *string1, const char *string2);
int     other_letters_check(char c);
int     first_letter_check(char letter);
int     is_number(char letter);
int     is_upper_case(char letter);
int     is_lower_case(char letter);
void	fill_up_double_pointer(char **split_line, const char *read_line);
char	**split_read_line(const char *read_line);
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
void    remove_quotes(t_token *tokens);
int     check_for_quote_without_quote_type(const char letter);
void    get_real_quote_type(const char *word, int *quote_type, int *i);
t_envs  *env_list_addition(t_token *tokens, t_envs *env_list);
int     dollar_sign_exception(const char *read_line, int *i, int *words);
int     is_heredoc_or_append(const char letter1, const char letter2);
int     is_special_character(const char *read_line, int i, int *letters);
int     is_redir_or_pipe(const char letter);
int     quote_in_word(const char *read_line, int *i, int *words);
int     syntax_error_message_display(const char *token_value);
int     is_dollar_sign(const char letter);
int     ft_strlen(const char *s);
int     is_pipe(const char letter);
int     syntax_check(t_token *tokens);
int     skip_to_next_dollar_sign(char *expandable);
int     tokenizer(char *input);
void    create_token_struct(t_token *tokens, char **line);
int     equal_sign_check(char *string);
int     env_assign_check(char *string);
int     check_for_redirect_out_and_append(const char *read_line, int *i);
int     check_for_redirect_in_and_heredoc(const char *read_line, int *i);
int     check_for_pipe(const char *read_line, int *i);
int     dollar_is_standing_alone(const char letter);
void    process_after_dollar_sign(const char *read_line, int *i, int *words);
int     is_dollar_after_dollar(const char letter);
int     is_redir(const char letter);
int     is_redir_in(const char letter);
int     is_redir_out(const char letter);
void    handle_expansions(t_envs *env_list, t_token *tokens);
int     is_astrisk(const char letter);
int     is_terminator(const char letter);
int     letter_after_dollar_is_num_or_astrisk(const char letter);
int     is_underline(char letter);
int     is_white_space_or_special_character(const char letter);
int     key_counter(const char *envp);
char    *get_full_expandable_word(t_token curr_token, t_envs *env_list, int len, int exit_code);
int     get_full_len_of_expandable(t_token curr_token, t_envs *env_list, t_token *token);
int     digit_counter(pid_t pid);
int     is_end(const char letter);
void    copy_till_next_quote(const char *read_line, int *i, char *new_word, int *new_index);
int     is_valid_after_dollar_sign(const char letter);
int     dollar_ended_naturally(const char *read_line, int i);
int     is_question_mark(const char letter);


#endif
