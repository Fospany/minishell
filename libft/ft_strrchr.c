/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:13:04 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/13 12:42:16 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = 0;
	if (*s == (unsigned char)c)
		r = (char *)s;
	while (*s++)
		if (*s == (unsigned char)c)
			r = (char *)s;
	return (r);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *str = "Hello, World!";
	char *res1 = ft_strrchr(str, 'o');
	char *std1 = strrchr(str, 'o');
	printf("Test 1: %s | %s\n", res1, std1);
}*/