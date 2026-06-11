/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:20:58 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/13 12:38:21 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{

	char s1[] = "Hello, World!", d1[20], d1_memmove[20];
	ft_memcpy(d1, s1+2, ft_strlen(s1) + 1);
	memcpy(d1_memmove, s1+2, ft_strlen(s1) + 1);
	printf("Test 1: %s | %s\n", d1, d1_memmove);

	return (0);
}*/