/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:02 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/04 11:32:49 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builts_check(char **str)
{
	if (!(ft_strcmp(str[0], "echo")) || \
		!(ft_strcmp(str[0], "pwd")) || \
		!(ft_strcmp(str[0], "env")) || \
		!(ft_strcmp(str[0], "cd")) || \
		!(ft_strcmp(str[0], "export")) || \
		!(ft_strcmp(str[0], "unset")) || \
		!(ft_strcmp(str[0], "exit")))
		return (1);
	return (0);
}

void	builts_run(char **str, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	if (!(ft_strcmp(str[0], "echo")))
		echo_built(str + 1, global);
	if (!(ft_strcmp(str[0], "pwd")))
		pwd_built();
	if (!(ft_strcmp(str[0], "env")))
		env_built(str, global->env_ment, global);
	if (!(ft_strcmp(str[0], "cd")))
		cd_built(str, global);
	if (!(ft_strcmp(str[0], "export")))
		export_built(str, global);
	if (!(ft_strcmp(str[0], "unset")))
		unset_built(str, global);
	if (!(ft_strcmp(str[0], "exit")))
		exit_built(str, arg, global, pid);
}
