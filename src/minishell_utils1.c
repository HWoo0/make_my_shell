/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:00 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 18:22:17 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcat(char *dst, const char *src)
{	
	int	i;
	int	j;
	int	dlen;
	int	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = dlen;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dlen + slen);
}

void	*ft_realloc(void *arr, int size, int new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(arr);
		return (NULL);
	}
	else if (arr == NULL)
		return (ft_calloc(sizeof(void *), new_size));
	new = ft_calloc(sizeof(void *), new_size);
	if (!new)
	{
		free(arr);
		return (NULL);
	}
	ft_memcpy(new, arr, size);
	free(arr);
	return (new);
}

char	*ft_getenv(t_global *global, char *str)
{
	int		i;
	char	**temp;
	char	*res;

	i = 0;
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(global->exit_stat));
	while (global->env_ment[i])
	{
		temp = ft_split(global->env_ment[i], '=');
		if (temp[1] && (ft_strcmp(temp[0], str) == 0))
		{
			res = ft_strdup(temp[1]);
			ft_free(temp);
			return (res);
		}
		ft_free(temp);
		i++;
	}
	return (NULL);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	if (!s2)
		len2 = 0;
	else
		len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}
