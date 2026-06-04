/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:12:40 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/13 12:36:49 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	size;

	size = ft_strlen(s);
	d = malloc(size + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, size);
	d[size] = '\0';
	return (d);
}

/*#include <stdio.h>
int	main(void)
{
	char *s1 = "hello";
	char *dup;

	dup = ft_strdup(s1);
	printf("Duplicate: %s\n", dup);
	free(dup);
}*/