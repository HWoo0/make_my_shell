/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:31 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/03 17:04:28 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**remove_env(ssize_t index, t_global *global)
{
	char	*tmp;
	size_t	i;
	size_t	size;

	i = index;
	size = env_count(global->env_ment);
	while (global->env_ment[i + 1])
	{
		tmp = ft_strdup(global->env_ment[i + 1]);
		free(global->env_ment[i]);
		global->env_ment[i] = tmp;
		i++;
	}
	return (realloc_envs((size - 1), global));
}

int	unset_built(char **str, t_global *global)
{
	size_t	i;
	ssize_t	index;

	global->exit_stat = 0;
	if (!str[1])
		return (1);
	i = 0;
	while (str[++i])
	{
		index = find_env(str[i], global);
		if (index != -1)
		{
			if (global->env_ment[index])
				global->env_ment = remove_env(index, global);
		}
	}
	return (global->exit_stat);
}
