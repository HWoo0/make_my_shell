/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:25:15 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/19 16:24:16 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_find(char const *s1, char const *set)
{
	int	s_i;
	int	i;

	s_i = 0;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1[s_i] == set[i])
		{
			s_i++;
			i = 0;
		}
		else
			i++;
	}
	return (s_i);
}

static int	end_find(char const *s1, char const *set)
{
	int	e_i;
	int	i;

	e_i = ft_strlen(s1) - 1;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1[e_i] == set[i] && e_i != 0)
		{
			e_i--;
			i = 0;
		}
		else
			i++;
	}
	return (e_i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_i;
	int		end_i;
	int		find_i;
	char	*str;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start_i = start_find(s1, set);
	end_i = end_find(s1, set);
	find_i = end_i - start_i + 1;
	if (start_i > end_i)
		return (ft_strdup(""));
	str = (char *)malloc((find_i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	result = str;
	while (find_i != 0)
	{
		*str++ = *(s1 + start_i++);
		find_i--;
	}
	*str = 0;
	return (result);
}
/*
#include <stdio.h>
int main()
{
	char *str1 = "abc123abc";
	char *str2 = "abcabc";
	char *str3 = 0;

	printf("%s\n", ft_strtrim(str1, "abc"));
	printf("%s\n", ft_strtrim(str2, "abc"));
	printf("%s\n", ft_strtrim(str3, "abc"));

	return 0;
}
*/
