/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:17 by bohchoi           #+#    #+#             */
/*   Updated: 2024/11/18 18:02:20 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_built(char **str, char **envp, t_global *global)
{
	int	i;

	i = 0;
	if (str[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd("': No such file or directory.\n", 2);
		global->exit_stat = 127;
	}
	else
	{
		while (envp[i])
		{
			if (ft_strchr(envp[i], '='))
			{
				write (1, envp[i], ft_strlen(envp[i]));
				write (1, "\n", 1);
			}
			i++;
		}
		global->exit_stat = 0;
	}
	return (global->exit_stat);
}
