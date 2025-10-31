/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:34:49 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/20 14:14:57 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	result;
	int				flag;
	int				i;

	result = 0;
	flag = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			flag *= -1;
		i++;
	}
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= 48 && nptr[i] <= 57)
			result = result * 10 + (nptr[i] - '0');
		else
			break ;
		i++;
	}
	return (flag * result);
}
/*
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *str = "	2147483648";

	printf("%d\n", atoi(str));
	printf("%d\n", ft_atoi(str));
	return 0;
}
*/
