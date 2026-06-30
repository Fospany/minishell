/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:42:45 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/04 15:09:32 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int equal_sign_check(char *string)
{
    int i;
    int equal_signs;
    
    equal_signs = 0;
    i = 0;
    while (string[i])
    {
        if (string[i] == EQUAL_SIGN)
            equal_signs++;
        i++;
    }
    if (equal_signs == 1)
        return (1);
    return (0);
}

int env_assign_check(char *string)
{
    int i;

    i = 0;
    if (!equal_sign_check(string))
        return (0);
    if (!first_letter_check(string[0]))
        return (0);
    while (string[i])
    {
        if (!other_letters_check(string[i]))
            return (0);
        i++;
    }
    return (1);
}

int first_letter_check(char letter)
{
    if (is_underline(letter) || is_lower_case(letter) || is_upper_case(letter))
        return (1);
    return (0);
}

int other_letters_check(char c)
{
    if (first_letter_check(c) || is_number(c) || c == EQUAL_SIGN)
        return (1);
    return (0);
}