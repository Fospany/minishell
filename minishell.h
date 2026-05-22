/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:20:37 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/22 09:58:48 by bguhty           ###   ########.fr       */
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

typedef struct s_token
{
    int             id;
    char            *value;
    t_token_type    type;
}                   t_token;

int     string_compare(char *string1, char *string2);
int     other_letters_check(char c);
int     first_letter_check(char letter);
int     is_not_number(char letter);
int     is_not_upper_case(char letter);
int     is_not_lower_case(char letter);
void	fill_up_double_pointer(char **split_line, const char *read_line);
char	**split(const char *read_line);
char	**allocating_double_pointer(const char *read_line);
int		count_letters(const char *read_line, int i);
int		word_counter(const char *read_line);
int		is_word(const char *read_line, int *words);
int		check_for_quote(const char letter, int *quote_type);
void    skip_white_spaces(const char *read_line, int *i);
int		is_white_space(const char letter);
void	skip_to_next_quote(const char *read_line, int *i, char quote_type);
void    skip_non_white_spaces(const char *read_line, int *i);
void    split_clean_up(char **split_line, int i);
int     env_assign_check(char *string);

#endif