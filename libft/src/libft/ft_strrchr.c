/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:15:21 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/18 21:43:39 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*p;

	p = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (p[len] == (char)c)
			return (p + len);
		len--;
	}
	return (NULL);
}
