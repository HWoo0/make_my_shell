/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:11:01 by bohchoi           #+#    #+#             */
/*   Updated: 2024/11/21 15:11:03 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	char_by_index(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - str));
}

int	ft_strequ(const char *s1, const char *s2)
{
	int	check;

	if (!s1 || !s2)
		return (0);
	check = ft_strcmp(s1, s2);
	if (check == 0)
		return (1);
	return (0);
}

char	*get_env(char *env, t_global *global)
{
	ssize_t	i;
	size_t	len;

	if (!env)
		return (NULL);
	len = ft_strlen(env);
	i = find_env(env, global);
	if (i != -1)
		return (ft_substr(global->env_ment[i], (len + 1), \
		ft_strlen(global->env_ment[i])));
	return (NULL);
}

ssize_t	find_env(char *env, t_global *global)
{
	char	*sub;
	ssize_t	i;
	ssize_t	idx;

	if (!env)
		return (-1);
	i = -1;
	sub = NULL;
	while (global->env_ment[++i])
	{
		idx = char_by_index(global->env_ment[i], '=');
		if (idx == -1)
			idx = ft_strlen(global->env_ment[i]);
		sub = ft_substr(global->env_ment[i], 0, idx);
		if (sub)
		{
			if (ft_strequ(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
	}
	return (-1);
}

size_t	env_count(char **env_ment)
{
	size_t	i;

	i = 0;
	while (env_ment[i])
		i++;
	return (i);
}
