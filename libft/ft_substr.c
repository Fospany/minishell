/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:47:37 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/09 12:51:16 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*str;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}
/*#include <stdio.h>
int	main(void)
{
	char *test1 = ft_substr("Hello, World!", 0, 5);
	printf("Test 1: \"%s\" (expected: Hello)\n", test1);
	free(test1);

	char *test2 = ft_substr("Hello, World!", 7, 5);
	printf("Test 2: \"%s\" (expected: World)\n", test2);
	free(test2);

	char *test3 = ft_substr("Hello, World!", 20, 5);
	printf("Test 3: \"%s\" (expected: empty string)\n", test3);
	free(test3);

	char *test4 = ft_substr("Hello", 0, 10);
	printf("Test 4: \"%s\" (expected: Hello)\n", test4);
	free(test4);

	char *test5 = ft_substr("", 0, 5);
	printf("Test 5: \"%s\" (expected: empty string)\n", test5);
	free(test5);

	return (0);
}*/