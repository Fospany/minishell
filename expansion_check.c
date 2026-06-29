/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:53:31 by guthybarnak       #+#    #+#             */
/*   Updated: 2026/06/29 18:27:42 by rici             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    copy_till_next_dollar(char *dest, char *source)
{
    int i;

    i = 0;
    while (source[i] && !is_dollar_sign(source[i]))
    {
        if (check_for_quote_without_quote_type(source[i]))
            break ;
        dest[i] = source[i];
        i++;
    }
    dest[i] = 0;
}

int     ft_strlen(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (i);
    while (s[i])
        i++;
    return (i);
}

int     dollar_in_word(char *word)
{
    int i;

    i = 0;
    while (word[i])
    {
        if (is_dollar_sign(word[i]))
            return (1);
        i++;
    }
    return (0);
}

char    *create_mock_word(char *expandable)
{
    char    *mock_word;
    
    mock_word = malloc(sizeof(char) * (count_letters_in_expansion(expandable + 1) + 1));
    if (!mock_word)
        return (NULL);
    copy_till_next_dollar(mock_word, expandable + 1);
    return (mock_word);
}

int     check_if_in_my_env_list(t_envs *env_list, char *expandable)
{
    int i;
    char    *new_word;

    new_word = malloc(sizeof(char) * (skip_to_next_dollar_sign(expandable) + 1));
    copy_till_next_dollar(new_word, expandable);
    i = 0;
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, new_word))
            return (1);
        i++;
    }
    return (0);
}

int     get_length_of_expansion(t_envs *env_list, char *expandable)
{
    int i;

    i = 0;
    while (env_list[i].value)
    {
        if (string_compare(env_list[i].key, expandable))
            return (ft_strlen(env_list[i].value));
        i++;
    }
    return (0);
}

int     count_letters_till_next_quote(char *word, int quote_type, int *i)
{
    int letters;

    letters = 0;
    (*i)++;
    while (word[*i])
    {
        if (word[*i] == quote_type)
        {
            (*i)++;
            return (letters);
        }
        letters++;
        (*i)++;
    }
    return (letters);
}

// int     get_full_len_of_expandable(char *expandable, t_envs *env_list)
// {
//     char    *mock_word;
//     int     i;
//     int     len;
//     int     quote_type;

//     quote_type = 0;
//     i = 0;
//     len = 0;
//     while (expandable[i])
//     {
//         mock_word = create_mock_word(expandable + i);
//         i += ft_strlen(mock_word);
//         len += get_length_of_expansion(env_list, mock_word);
//         if (check_for_quote(expandable[i], &quote_type))
//             len += count_letters_till_next_quote(expandable, quote_type, &i);
//         i++;
//     }
//     return (len);
// }

int     invalid_for_after_dollar(const char letter)
{
    if (letter == DOLLAR_SIGN)
        return (1);
    else if (check_for_quote_without_quote_type(letter))
        return (1);
    else
        return (0);
}

int     count_letters_in_expansion(char *expandable)
{
    int i;

    i = 0;
    while (expandable[i])
    {
        if (invalid_for_after_dollar(expandable[i]))
            return (i);
        i++;
    }
    return (i);
}

int    copy_from_env_list(t_envs *env_list, char *expandable, char *fully_expanded, int *index)
{
    int i;
    int j;
    char    *new_word;

    i = 0;
    j = 0;
    new_word = malloc(sizeof(char) * (skip_to_next_dollar_sign(expandable) + 1));
    copy_till_next_dollar(new_word, expandable);
    while (env_list[i].key != NULL)
    {
        if (string_compare(env_list[i].key, new_word))
        {
            while (env_list[i].value[j])
                fully_expanded[(*index)++] = env_list[i].value[j++];
            return (ft_strlen(new_word));
        }
        i++;
    }
    return (j);
}

int     copy_until_next_quote(const char *expandable, char *fully_expanded, int *index, int *quote_type)
{
    int i;

    i = 0;
    while (expandable[i])
    {
        if (check_for_quote(expandable[i], quote_type))
            return (i);
        else
            fully_expanded[(*index)++] = expandable[i++];
    }
    return (i);
}

int     digit_counter(pid_t pid)
{
    int digits;

    digits = 0;
    while (pid > 0)
    {
        pid /= 10;
        digits++;
    }
    return (digits);
}

char    *my_itoa(pid_t pid)
{
    int     digits;
    char    *pid_string;

    pid = (int)pid;
    digits = digit_counter(pid);
    pid_string = malloc(sizeof(char) * (digits + 1));
    pid_string[digits] = 0;
    while (pid > 0)
    {
        pid_string[--digits] = pid % 10 + '0';
        pid /= 10;
    }
    return (pid_string);
}

void    handle_double_dollars(char *fully_expanded, int *index)
{
    char    *pid;
    int     i;

    i = 0;
    pid = my_itoa(getpid());
    while (pid[i])
        fully_expanded[(*index)++] = pid[i++];
}

int     check_in_real_environment_list(char *expandable)
{
    if (getenv(expandable))
        return (1);
    return (0);
}

// char    *create_the_whole_word(char *expandable, t_envs *env_list, int token_type)
// {
//     int     i;
//     int     j;
//     int     quote_type;
//     char    *fully_expanded;

//     fully_expanded = malloc(sizeof(char) * (get_full_len_of_expandable(expandable, env_list) + 2));
//     quote_type = 0;
//     i = 0;
//     j = 0;
//     while (expandable[i])
//     {
//         if (is_dollar_sign(expandable[i]))
//         {
//             if (is_dollar_after_dollar(expandable[i + 1]))
//             {
//                 handle_double_dollars(fully_expanded, &j);
//                 i += 2;
//             }
//             else if (check_if_in_my_env_list(env_list, expandable + i))
//                 i += copy_from_env_list(env_list, expandable  + i, fully_expanded, &j);
//             else if (check_in_real_environment_list(expandable + i))
//             {
//                 copy_from_real_environment_list(expandable + i, fully_expanded, &j);
//             }
//             else
//             {
//                 fully_expanded[j] = 0;
//                 return (fully_expanded);
//             }
//         }
//         else if (check_for_quote(expandable[i], &quote_type))
//         {
//             i++;
//             i += copy_until_next_quote(expandable + i, fully_expanded, &j, &quote_type);
//         }
//         else
//             fully_expanded[j++] = expandable[i++];
//     }
//     fully_expanded[j] = 0;
//     return (fully_expanded);
// }

char    *copy_till_equal_sign(char *expandable)
{
    int     i;
    char    *new_key;

    i = 0;
    new_key = malloc(sizeof(char) * (key_counter(expandable) + 1));
    while (expandable[i] != EQUAL_SIGN)
    {
        new_key[i] = expandable[i];
        i++;
    }
    new_key[i] = 0;
    return (new_key);
}

char    *copy_for_env_assign(char *env_assign_value)
{
    char    *new_word;
    int     i;
    
    i = 0;
    new_word = malloc(sizeof(char) * (ft_strlen(env_assign_value) + 1));
    while (env_assign_value[i])
    {
        new_word[i] = env_assign_value[i];
        i++;
    }
    new_word[i] = 0;
    return (new_word);
}

char    *expand_env_assign(char *expandable, t_envs *env_list, int *index)
{
    char    *new_key;
    char    *new_word;
    int     i;
    
    i = 0;
    new_key = copy_till_equal_sign(expandable);
    while (!string_compare(new_key, env_list[i].key))
        i++;
    new_word = copy_for_env_assign(env_list[i].value);
    (*index) += ft_strlen(new_word);
    return (new_word);
}

void    handle_expansions(t_envs *env_list, t_token *tokens)
{
    int i;
    int len;
    
    i = 0;
    while (tokens[i].value)
    {
        if (dollar_in_word(tokens[i].value) && tokens[i].quote_type != SINGLE_QUOTE)
        {
            len = get_full_len_of_expandable(tokens[i], env_list);
            tokens[i].value = get_full_expandable_word(tokens[i], env_list, len);
        }
        i++;
    }
}

int     is_valid_after_dollar_sign(const char letter)
{
    if (!is_number(letter) && !is_upper_case(letter) && !is_lower_case(letter) && !is_underline(letter))
        return (0);
    return (1);
}

int     get_len_of_valid_expandable(const char *expandable)
{
    int len;

    len = 0;
    while (expandable[len])
    {
        if (!is_valid_after_dollar_sign(expandable[len]))
            break ;
        len++;
    }
    return (len);
}

char    *get_valid_expandable(const char *expandable)
{
    int     i;
    int     len;
    char    *valid_expandable;

    i = 0;
    len = get_len_of_valid_expandable(expandable);
    valid_expandable = malloc(sizeof(char) * (len + 1));
    while (i < len)
    {
        valid_expandable[i] = expandable[i];
        i++;
    }
    valid_expandable[i] = 0;
    return (valid_expandable);
}

char    *get_from_my_env_list(const char *expandable, t_envs *env_list)
{
    while (env_list->key)
    {
        if (string_compare(expandable, env_list->key))
            return (env_list->value);
    }
    return (NULL);
}

int     get_len_of_current_expandable(const char *expandable, t_envs *env_list)
{
    char    *test_env;
    char    *real_env;
    int     len;

    test_env = get_valid_expandable(expandable);
    real_env = getenv(test_env);
    if (!real_env)
        real_env = get_from_my_env_list(test_env, env_list);
    len = ft_strlen(real_env);
    return (len);
}

int     count_valid_characters_after_dollar_sign(const char *curr_expandable)
{
    int i;

    i = 1;
    while (curr_expandable[i])
    {
        if (!is_valid_after_dollar_sign(curr_expandable[i]))
            break ;
        i++;
    }
    return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

int     get_full_len_of_expandable(t_token curr_token, t_envs *env_list)
{
    int     i;
    int     len;

    i = 0;
    len = 0;
    while (curr_token.value[i])
    {
        if (is_dollar_sign(curr_token.value[i]))
        {
            len += get_len_of_current_expandable(&curr_token.value[i + 1], env_list);
            i += count_valid_characters_after_dollar_sign(&curr_token.value[i]);
        }
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

void    cat_to_fully_expanded(char *fully_expanded, const char new_letter)
{
    int index;

    index = ft_strlen(fully_expanded);
    fully_expanded[index] = new_letter;
}

void    make_expansion(char *fully_expnaded, const char *mock_expand, int *i, t_envs *env_list)
{
    int     expand_index;
    char    *test_env;
    int     env_index;

    env_index = 0;
    expand_index = ft_strlen(fully_expnaded);
    (*i) += (ft_strlen(mock_expand) + 1);
    test_env = getenv(mock_expand);
    if (!test_env)
        test_env = get_from_my_env_list(mock_expand, env_list);
    if (test_env)
    {
        while (test_env[env_index])
        {
            fully_expnaded[expand_index] = test_env[env_index];
            expand_index++;
            env_index++;
        }
    }
}

char    *get_full_expandable_word(t_token curr_token, t_envs *env_list, int len)
{
    char    *fully_expanded;
    char    *mock_expand;
    int i;

    i = 0;
    fully_expanded = ft_calloc(sizeof(char), (len + 1));
    if (!fully_expanded)
        return (NULL);
    while (curr_token.value[i])
    {
        if (is_dollar_sign(curr_token.value[i]))
        {
            mock_expand = get_valid_expandable(curr_token.value + i + 1);
            make_expansion(fully_expanded, mock_expand, &i, env_list);
        }
        else
            cat_to_fully_expanded(fully_expanded, curr_token.value[i++]);
    }
    fully_expanded[len] = 0;
    return (fully_expanded);
}
