/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:22 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/13 13:39:15 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (src > dest)
	{
		while (n--)
			*d++ = *s++;
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{

	char s1[] = "Hello, World!", d1[20], d1_memmove[20];
	//ft_memmove(d1, s1, 0);
	memmove(d1_memmove, NULL, 3);
	printf("Test 1: %s | %s\n", d1, d1_memmove);

	return (0);
}*/