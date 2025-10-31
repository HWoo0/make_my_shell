/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_creatcmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:20:37 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 15:44:09 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**dup_arg(char **arg)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_calloc(1, sizeof(char *));
	while (arg[i])
	{
		res = ft_realloc(res, sizeof(char *) * (i + 1), \
			sizeof(char *) * (i + 2));
		res[i] = ft_strdup(arg[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**cutting_pipe(char **str, int *index)
{
	char	**res;
	int		k;

	k = 0;
	res = ft_calloc(1, sizeof(char *));
	if (ft_strcmp(str[*index], "|") == 0)
		(*index)++;
	while (str[*index] && ft_strcmp(str[*index], "|") != 0)
	{
		if (*str[*index])
		{
			res = ft_realloc(res, sizeof(char *) * (k + 1), \
				sizeof(char *) * (k + 2));
			res[k++] = ft_strdup(str[*index]);
		}
		(*index)++;
	}
	res[k] = NULL;
	return (res);
}

char	**creat_cmd(char **argv, int *index, t_fd *fd, t_global *global)
{
	char	**cutting_arg;
	char	**cmd;
	char	**temp;

	cutting_arg = cutting_pipe(argv, index);
	temp = dup_arg(cutting_arg);
	if (temp == NULL)
		return (NULL);
	ft_ifenvp(cutting_arg, global);
	remove_quote(&cutting_arg, temp, global);
	if (ft_creat_file(&cutting_arg, global) == NULL)
		return (NULL);
	cmd = ft_redirection_file(cutting_arg, fd, global, 0);
	reset_io(fd);
	ft_free(cutting_arg);
	ft_free(temp);
	return (cmd);
}
