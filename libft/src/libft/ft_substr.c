/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:16:28 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/18 16:10:04 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*result;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	else if (start + len > s_len)
		str = (char *)malloc((s_len - start + 1) * sizeof(char));
	else
		str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	result = str;
	while (*(s + start) && len != 0)
	{
		*str++ = *(s + start++);
		len--;
	}
	*str = 0;
	return (result);
}
/*
#include <stdio.h>

int main()
{
	char *str = "1243567890";
	char *test1 = ft_substr(str, 5, 3);
	char *test2 = ft_substr(str, 8, 3);
	char *test3 = ft_substr(str, 11, 2);

	printf("%s\n", test1);
	printf("%s\n", test2);
	printf("%s\n", test3);

	return 0;
}
*/
