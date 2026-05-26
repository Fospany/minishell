/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guthybarnakoppany <guthybarnakoppany@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:00:28 by bguhty            #+#    #+#             */
/*   Updated: 2026/05/26 11:39:06 by guthybarnak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_not_lower_case(char letter)
{
    if (!(letter >= a && letter <= z))
        return (1);
    return (0);
}

int is_not_upper_case(char letter)
{
    if (!(letter >= A && letter <= Z))
        return (1);
    return (0);
}

int is_not_number(char letter)
{
    if (!(letter >= '0' && letter <= '9'))
        return (1);
    return (0);
}

int is_not_underline(char letter)
{
    if (letter != '_')
        return (1);
    return (0);
}

int first_letter_check(char letter)
{
    if (is_not_lower_case(letter) && is_not_upper_case(letter) && is_not_underline(letter))
        return (1);
    return (0);
}

int other_letters_check(char c)
{
    if (first_letter_check(c) || is_not_number(c) || c != EQUAL_SIGN)
        return (0);
    return (1);
}
