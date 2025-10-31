/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:04:22 by bohchoi           #+#    #+#             */
/*   Updated: 2024/11/18 18:04:25 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_built(char **str, t_global *global)
{
	size_t	i;

	global->exit_stat = 0;
	if (!str[1])
	{
		sort_export(global);
		return (1);
	}
	i = 0;
	while (str[++i])
	{
		if (!name_check(str[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd("': Not a valid identifier\n", 2);
			global->exit_stat = 1;
			continue ;
		}
		update_export(str, i, global);
	}
	return (global->exit_stat);
}

void	new_env_free(char *env_name, char *end)
{
	free(env_name);
	free(end);
}
