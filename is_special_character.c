/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:35:58 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/03 17:51:30 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_terminator(const char letter)
{
    if (letter == '\0')
        return (1);
    return (0);
}

int     is_astrisk(const char letter)
{
    if (letter == '*')
        return (1);
    return (0);
}
