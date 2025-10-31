/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:40:11 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/18 14:41:01 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_negative(int *n, int *n_len, int *sign, char **str)
{
	if (*n == -2147483648)
	{
		(*str)[(*n_len)--] = 8 + '0';
		(*n) /= 10;
	}
	if (*n < 0)
	{
		(*sign) *= -1;
		(*n) *= -1;
	}
}

char	*ft_itoa(int n)
{
	int		n_len;
	int		sign;
	int		num;
	char	*str;

	n_len = num_digits(n);
	sign = 1;
	str = (char *)malloc((n_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[n_len--] = '\0';
	ft_negative(&n, &n_len, &sign, &str);
	while (n_len >= 0)
	{
		num = n % 10;
		str[n_len] = num + '0';
		n /= 10;
		n_len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
/*
#include <stdio.h>
int main()
{
	int	num1 = 1234;
	printf("%s\n", ft_itoa(num1));
	int	num2 = -1234;
	printf("%s\n", ft_itoa(num2));
	int	num3 = -2147483648;
	printf("%s\n", ft_itoa(num3));
	int	num4 = -0;
	printf("%s\n", ft_itoa(num4));

	return 0;
}
*/
