/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:50 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 15:44:07 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*rm_quote(char *str)
{
	char	*new;

	if (str[0] == '\'' || str[0] == '\"')
		new = ft_strldup(str + 1, ft_strlen(str) - 2);
	else
		new = ft_strdup(str);
	return (new);
}

static void	*is_redirc_in(char **line, int i, t_fd *fd, t_global *global)
{
	char	*file_name;

	file_name = rm_quote(line[i]);
	fd->fd1 = open(file_name, O_RDONLY);
	if (fd->fd1 < 0)
	{
		ft_putstr_fd("file error\n", 2);
		global->exit_stat = 1;
		global->err_flag = 1;
		return (NULL);
	}
	if (!ft_strcmp(line[i - 1], "<<"))
		unlink(file_name);
	free(file_name);
	return (line);
}

static void	*is_redirc_out(char **line, int i, t_fd *fd, t_global *global)
{
	char	*file_name;

	file_name = rm_quote(line[i]);
	if (!ft_strcmp(line[i - 1], ">>"))
		fd->fd2 = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd->fd2 = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd->fd2 < 0)
	{
		ft_putstr_fd("file error\n", 2);
		global->exit_stat = 1;
		global->err_flag = 1;
		return (NULL);
	}
	free(file_name);
	return (line);
}

static void	not_redirec(char ***res, char *line, int *k, t_global *global)
{
	*res = ft_realloc(*res, sizeof(char *) * (*k + 1), \
		sizeof(char *) * (*k + 2));
	if (!(*res))
		ft_free(*res);
	(*res)[(*k)++] = ft_strdup(line);
	global->err_flag = 0;
}

char	**ft_redirection_file(char **line, t_fd *fd, t_global *global, int i)
{
	int		k;
	char	**res;

	k = 0;
	res = ft_calloc(1, sizeof(char *));
	if (!res)
		return (NULL);
	while (line[i])
	{
		if (!ft_strcmp(line[i], "<") || !ft_strcmp(line[i], "<<"))
		{
			if (!is_redirc_in(line, ++i, fd, global))
				return (NULL);
		}
		else if (!ft_strcmp(line[i], ">") || !ft_strcmp(line[i], ">>"))
		{
			if (!is_redirc_out(line, ++i, fd, global))
				return (NULL);
		}
		else
			not_redirec(&res, line[i], &k, global);
		i++;
	}
	res[k] = NULL;
	return (res);
}
