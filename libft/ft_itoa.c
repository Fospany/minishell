/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:27:11 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/09 11:14:38 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int		i;
	long	long_n;

	long_n = n;
	i = 0;
	if (long_n == 0)
		i++;
	if (long_n < 0)
	{
		long_n = long_n * -1;
		i++;
	}
	while (long_n > 0)
	{
		long_n = long_n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	long_n;

	len = int_len(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	long_n = n;
	if (long_n == 0)
		str[0] = '0';
	if (long_n < 0)
	{
		long_n = long_n * -1;
		str[0] = '-';
	}
	while (long_n > 0)
	{
		str[--len] = (long_n % 10) + '0';
		long_n /= 10;
	}
	str[int_len(n)] = '\0';
	return (str);
}

/*#include <stdio.h>
int	main(void)
{
	char *res1 = ft_itoa(0);
	printf("Test 1: %s (expected: 0)\n", res1);
	free(res1);

	char *res2 = ft_itoa(42);
	printf("Test 2: %s (expected: 42)\n", res2);
	free(res2);

	char *res3 = ft_itoa(-42);
	printf("Test 3: %s (expected: -42)\n", res3);
	free(res3);

	char *res4 = ft_itoa(2147483647);
	printf("Test 4: %s (expected: 2147483647)\n", res4);
	free(res4);

	char *res5 = ft_itoa(-2147483648);
	printf("Test 5: %s (expected: -2147483648)\n", res5);
	free(res5);

	char *res6 = ft_itoa(1000000);
	printf("Test 6: %s (expected: 1000000)\n", res6);
	free(res6);

	return (0);
}*/