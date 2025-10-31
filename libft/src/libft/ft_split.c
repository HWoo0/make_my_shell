/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:08:56 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/18 16:04:25 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	get_height(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static int	get_width(char const *s, char c, char **arr, int i)
{
	int	len;

	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = 0;
			while (*s != c && *s)
			{
				s++;
				len++;
			}
			arr[i] = (char *)malloc((len + 1) * sizeof(char));
			if (!arr[i])
			{
				get_free(arr);
				return (-1);
			}
			ft_strlcpy((char *)arr[i], (char *)s - len, len + 1);
			i++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		width;

	if (!s)
		return (NULL);
	arr = (char **)malloc((get_height(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	width = get_width(s, c, arr, 0);
	if (width == -1)
		return (NULL);
	arr[get_height(s, c)] = 0;
	return (arr);
}
