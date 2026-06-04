/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:30:43 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/09 12:32:42 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

/*#include <stdio.h>
int	main(void)
{
	char *res1 = ft_strjoin("Hello, ", "World!");
	printf("Test 1: %s (expected: Hello, World!)\n", res1);
	free(res1);

	char *res2 = ft_strjoin("", "World!");
	printf("Test 2: %s (expected: World!)\n", res2);
	free(res2);

	char *res3 = ft_strjoin("Hello, ", "");
	printf("Test 3: %s (expected: Hello, )\n", res3);
	free(res3);

	char *res4 = ft_strjoin("", "");
	printf("Test 4: %s (expected: empty string)\n", res4);
	free(res4);

	char *res5 = ft_strjoin("42", " Network");
	printf("Test 5: %s (expected: 42 Network)\n", res5);
	free(res5);

	return (0);
}*/