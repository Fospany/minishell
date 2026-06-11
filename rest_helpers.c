/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:26:24 by bguhty            #+#    #+#             */
/*   Updated: 2026/06/04 15:39:27 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int string_compare(char *string1, char *string2)
{
    int i;
    
    i = 0;
    while (string1[i] && string2[i])
    {
        if (string1[i] != string2[i])
            return (0);
        i++;
    }
    return (1);
}
