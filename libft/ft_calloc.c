/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:27:52 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/13 12:49:43 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*#include <stdio.h>
int	main(void)
{
	int i;
	int *arr1 = ft_calloc(-1, sizeof(int));
	int *arr1_std = calloc(-1, sizeof(int));

	i = 0;
	printf("Test: ");
	while (i < 5)
	{
		printf("%d ", arr1[i]);
		i++;
	}
	i = 0;
	printf("| ");
	while (i < 5)
	{
		printf("%d ", arr1_std[i]);
		i++;
	}
	printf("\n");
	free(arr1);
	free(arr1_std);
}*/