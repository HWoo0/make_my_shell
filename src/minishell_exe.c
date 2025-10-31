/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:13 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/11/30 13:33:47 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_pipe(char **argv)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i++], "|") == 0)
			cnt++;
	}
	return (cnt);
}

static int	cnt_arg(char **argv)
{
	int	j;
	int	argc;

	j = 0;
	argc = 1;
	while (argv[j])
	{
		if (ft_strcmp(argv[j], "|") == 0)
			argc++;
		j++;
	}
	return (argc);
}

void	exe_cmd(char **argv, t_fd fd, t_global *global)
{
	t_cmd_arg	arg;

	arg.flag = 0;
	arg.argc = cnt_arg(argv);
	arg.pipe_cnt = count_pipe(argv);
	arg.fd = fd;
	fd_init(&arg.fd, arg.argc);
	running_cmd(argv, &arg, global);
	signal(SIGINT, sigfunc);
	reset_io(&fd);
}
