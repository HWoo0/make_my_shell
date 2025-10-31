/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:10:37 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 10:15:46 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fd_init(t_fd *fd, int argc)
{
	int	i;

	i = 0;
	fd->fd1 = 0;
	fd->fd2 = 0;
	fd->pipe = malloc(sizeof(int *) * argc);
	if (!fd->pipe)
		return ;
	while (i < argc)
		fd->pipe[i++] = ft_calloc(sizeof(int), 2);
	fd->cmd_num = 0;
}

void	fd_close_free(t_fd *fd, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		close(fd->pipe[i][0]);
		close(fd->pipe[i][1]);
		free(fd->pipe[i++]);
	}
	free(fd->pipe);
}

void	reset_io(t_fd *fd)
{
	dup2(fd->temp_in, STDIN_FILENO);
	dup2(fd->temp_out, STDOUT_FILENO);
}
