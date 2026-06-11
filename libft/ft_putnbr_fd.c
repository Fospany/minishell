/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:54 by dabdulla          #+#    #+#             */
/*   Updated: 2025/10/09 11:30:37 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + 48;
	write(fd, &c, 1);
}

/*#include <fcntl.h>
int	main(void)
{
	int i = -2147483648;
	int fd;

	fd = open("ints.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(i, fd);
	close(fd);
}*/