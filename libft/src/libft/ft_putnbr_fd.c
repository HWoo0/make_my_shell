/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:59:42 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/16 17:34:41 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		n %= 10;
	}
	if (n < 10)
	{
		temp = n + '0';
		write(fd, &temp, 1);
	}
}
/*
#include<unistd.h>
int main()
{
	int num1 = -2147483648;
	ft_putnbr_fd(num1, 1);
	write(1, "\n", 1);
	int num2 = 2147483647;
	ft_putnbr_fd(num2, 1);
	write(1, "\n", 1);
	int num3 = -214746;
	ft_putnbr_fd(num3, 1);
	write(1, "\n", 1);
	int num4 = 100;
	ft_putnbr_fd(num4, 1);
}
*/
