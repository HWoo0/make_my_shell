/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_runningcmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:29:30 by hyeojeon          #+#    #+#             */
/*   Updated: 2025/03/11 16:24:15 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	all_free(char ***cmd, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	int	i;

	i = 0;
	ft_free(*cmd);
	while (i < arg->argc)
		free(arg->fd.pipe[i++]);
	free(arg->fd.pipe);
	ft_free(global->arg.res);
	ft_free(global->env_ment);
	free(*pid);
}

static void	pid_init(pid_t **pid, int argc)
{
	int	i;

	*pid = malloc(sizeof(pid_t) * (argc + 1));
	i = 0;
	while (i < argc)
		(*pid)[i++] = -1;
}

static void	exit_stat_update(int argc, pid_t *pid, t_global *global)
{
	int	proc;
	int	stat;

	proc = 0;
	while (proc < argc && pid[proc] != -1)
	{
		waitpid(pid[proc], &stat, 0);
		if (global->err_flag)
			return ;
		if (WIFSIGNALED(stat))
		{	
			global->exit_stat = 128 + WTERMSIG(stat);
			if (global->exit_stat == 130)
				printf("\n");
			if (global->exit_stat == 131)
				printf("Quit (core dump)\n");
		}
		else
			global->exit_stat = WEXITSTATUS(stat);
		proc++;
	}
}

static void	running_cmd2(char **cmd, t_cmd_arg *arg, \
							t_global *global, pid_t **pid)
{
	if (arg->pipe_cnt == 0 && arg->flag == 1 && ft_strcmp(cmd[0], "echo"))
		builts_run(cmd, arg, global, pid);
	else
	{
		pipe(arg->fd.pipe[arg->fd.cmd_num]);
		(*pid)[arg->fd.cmd_num] = fork();
		if ((*pid)[arg->fd.cmd_num] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (global->err_flag != 2)
				op_exe(cmd, arg, global, pid);
			all_free(&cmd, arg, global, pid);
			exit(0);
		}
	}
}

void	running_cmd(char **argv, t_cmd_arg *arg, t_global *global)
{
	pid_t	*pid;
	int		index;
	char	**cmd;

	pid_init(&pid, arg->argc);
	index = 0;
	while (argv[index])
	{
		arg->fd.fd1 = 0;
		arg->fd.fd2 = 0;
		cmd = creat_cmd(argv, &index, &arg->fd, global);
		opinit(&cmd, global, &arg->flag);
		running_cmd2(cmd, arg, global, &pid);
		signal(SIGINT, SIG_IGN);
		arg->fd.cmd_num++;
		reset_io(&arg->fd);
		if (cmd)
			ft_free(cmd);
	}
	fd_close_free(&arg->fd, arg->argc);
	exit_stat_update(arg->argc, pid, global);
	free(pid);
}
