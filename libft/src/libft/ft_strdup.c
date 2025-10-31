/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:33:04 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/12 22:11:19 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*str;
	char	*result;

	len = ft_strlen(s) + 1;
	str = (char *)malloc(len * sizeof(char));
	result = str;
	if (!str)
		return (NULL);
	while (*s)
		*str++ = *s++;
	*str = '\0';
	return (result);
}
