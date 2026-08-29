/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rici <rici@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:26:24 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/30 14:20:33 by rici             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int string_compare(const char *string1, const char *string2)
{
    int i;

    i = 0;
    while (string1[i] || string2[i])
    {
        if (string1[i] != string2[i])
            return (0);
        i++;
    }
    if (string1[i] == '\0' && string2[i] == '\0')
   		return (1);
    return (0);
}
