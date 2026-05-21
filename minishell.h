/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguthy <bguthy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 14:00:32 by bguthy            #+#    #+#             */
/*   Updated: 2026/05/21 17:08:38 by bguthy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define a 97
# define z 122
# define A 65
# define Z 90
# define SPACE 32
# define HORIZONTAL_TAB 9
# define CARRIAGE_RET 13
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"

void	fill_up_double_pointer(char **split_line, const char *read_line);
char	**split(const char *read_line);
char	*copy_n_chars(int start, int end, const char *read_line);
char	**allocating_double_pointer(const char *read_line);
int		count_letters(const char *read_line, int i);
int		word_counter(const char *read_line);
int		is_word(const char *read_line, int *words);
int		check_for_quote(const char letter, int *quote_type);
int		skip_white_spaces(const char *read_line);
int		is_white_space(const char letter);
int		skip_to_next_quote(const char *read_line, char quote_type);
int     skip_non_white_spaces(const char *read_line);

#endif