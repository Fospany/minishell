/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:55:00 by dabdulla          #+#    #+#             */
/*   Updated: 2026/03/26 12:30:42 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!set)
		return (0);
	while (set[j] && s1[i])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
			continue ;
		}
		j++;
	}
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	count;

	if (!set || !s1 || *s1 == '\0')
		return (0);
	i = ft_strlen(s1) - 1;
	j = 0;
	count = 0;
	if (!set)
		return (0);
	while (set[j] && i >= 0)
	{
		if (set[j] == s1[i])
		{
			i--;
			count++;
			j = 0;
			continue ;
		}
		j++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	int		start;
	char	*str;

	if (!s1)
		return (NULL);
	start = find_start(s1, set);
	size = ft_strlen(s1) - start - find_end(s1, set);
	if (size <= 0)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1 + start, size);
	str[size] = '\0';
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	char *s1 = "-- -t- est- --";
	char *set;
	set = NULL;
	printf("Trimmed: %s\n", ft_strtrim(s1, set));
}*/
