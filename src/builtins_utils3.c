/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:37:45 by bohchoi           #+#    #+#             */
/*   Updated: 2024/11/21 15:37:46 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	modify(char *new_env, size_t len, ssize_t i, t_global *global)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr(global->env_ment[i], 0, (len + 1));
	if (!tmp)
		return (0);
	new = ft_strjoin(tmp, new_env);
	if (!new)
		return (0);
	free(global->env_ment[i]);
	free(tmp);
	global->env_ment[i] = new;
	return (1);
}

int	set_env(char *env, char *new_env, t_global *global)
{
	char	*tmp;
	ssize_t	i;
	size_t	len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = -1;
	i = find_env(env, global);
	if (i != -1)
		return (modify(new_env, len, i, global));
	else
	{
		len = env_count(global->env_ment) + 1;
		global->env_ment = realloc_envs(len, global);
		tmp = ft_strjoin(env, "=");
		global->env_ment[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}

char	**realloc_envs(size_t size, t_global *global)
{
	char	**new;
	size_t	i;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (global->env_ment[i] && i < size)
	{
		new[i] = ft_strdup(global->env_ment[i]);
		i++;
	}
	new[size] = 0;
	ft_free_array(global->env_ment);
	return (new);
}

void	ft_free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	export_free(char *env_name, char *end, t_global *global)
{
	if (set_env(env_name, end, global))
	{
		free(env_name);
		free(end);
		return (0);
	}
	free(env_name);
	free(end);
	return (1);
}
