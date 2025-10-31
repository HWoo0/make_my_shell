/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:01:46 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/03 17:04:17 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*add_home_path(char *path, t_global *global)
{
	char	*tmp;
	char	*temp;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp = get_env("HOME", global);
		if (tmp)
		{
			temp = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, temp);
			free(temp);
			free(tmp);
			return (path);
		}
	}
	return (path);
}

static int	change(char *path, int home, t_global *global)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd, global);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", pwd, global);
			free(pwd);
		}
		if (home)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

int	s_path(char **str, t_global *global)
{
	char	*temp;

	if (ft_strequ(str[1], "-"))
	{
		temp = get_env("OLDPWD", global);
		if (temp)
		{
			set_dir(temp, 0, global);
			free(temp);
		}
		temp = get_env("PWD", global);
		if (temp)
		{
			ft_putstr_fd(temp, 1);
			free(temp);
			ft_putchar_fd('\n', 1);
		}
		return (1);
	}
	return (set_dir(str[1], 0, global));
}

int	set_dir(char *path, int home, t_global *global)
{
	struct stat	st;

	if (change(path, home, global))
		return (1);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	global->exit_stat = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);
		global->exit_stat = 1;
	}
	else
		ft_putstr_fd("Not a directory", 2);
	ft_putchar_fd('\n', 2);
	if (home)
		free(path);
	return (1);
}

int	cd_built(char **str, t_global *global)
{
	char	*home;

	global->exit_stat = 0;
	home = NULL;
	if (str && str[1] && str[2])
	{
		ft_putstr_fd("too many argument\n", 2);
		global->exit_stat = 1;
		return (1);
	}
	if (!str[1] || ft_strequ(str[1], "~") || ft_strequ(str[1], "--"))
	{
		home = get_env("HOME", global);
		if (!home)
		{
			ft_putstr_fd("HOME not set\n", 2);
			return (1);
		}
		return (set_dir(home, 1, global));
	}
	str[1] = add_home_path(str[1], global);
	return (s_path(str, global));
}
