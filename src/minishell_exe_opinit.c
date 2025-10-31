/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_opinit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:16:17 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 18:15:07 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*find_case(char *op, char **temp)
{
	char	*str;
	char	*t1;
	char	*t2;
	int		i;

	i = 0;
	while (temp[i])
	{
		str = ft_strchr(temp[i], '=');
		if (str)
			str++;
		else
			str = temp[i];
		t1 = ft_strjoin(str, "/");
		if (!t1)
			return (NULL);
		t2 = ft_strjoin(t1, op);
		free(t1);
		if (access(t2, X_OK) == 0)
			return (t2);
		free(t2);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *op, t_global *global)
{
	char	**temp;
	char	*res;
	char	*path_env;

	path_env = ft_getenv(global, "PATH");
	if (!path_env)
		return (NULL);
	temp = ft_split(path_env, ':');
	free(path_env);
	if (!temp)
		return (NULL);
	res = find_case(op, temp);
	ft_free(temp);
	return (res);
}

static void	*dir_check(char *str, t_global *global)
{
	struct stat	statbuf;

	if (stat(str, &statbuf) == 0)
	{
		if (access(str, F_OK) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				if (str[0] == '/' || \
					(str[0] == '.' && str[1] == '/') || \
					(str[0] == '.' && str[1] == '.' && str[2] == '/'))
				{
					global->err_flag = 2;
					global->exit_stat = 126;
					ft_putstr_fd("is directory\n", 2);
				}
				return (NULL);
			}
		}
	}
	return (str);
}

static void	*is_exeable(char *str, t_global *global)
{
	struct stat	statbuf;

	if (stat(str, &statbuf) == 0)
	{
		if (str[0] == '/' || \
			(str[0] == '.' && str[1] == '/') || \
			(str[0] == '.' && str[1] == '.' && str[2] == '/'))
		{
			if (S_ISREG(statbuf.st_mode))
			{
				if (access(str, X_OK) != 0)
				{
					global->err_flag = 2;
					global->exit_stat = 126;
					ft_putstr_fd("access error\n", 2);
				}
				return (NULL);
			}
		}
	}
	return (str);
}

void	opinit(char ***arg, t_global *global, int *flag)
{
	char		*temp;

	if (*arg == NULL)
		return ;
	*flag = builts_check(*arg);
	if (*flag)
		return ;
	if (!is_exeable((*arg)[0], global))
		return ;
	if (!dir_check((*arg)[0], global))
		return ;
	temp = find_path((*arg)[0], global);
	if (!temp)
	{
		global->err_flag = 2;
		global->exit_stat = 127;
		ft_putstr_fd("execve error\n", 2);
		return ;
	}
	free((*arg)[0]);
	(*arg)[0] = temp;
}
