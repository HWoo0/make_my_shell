/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_opexe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:28:04 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/12 14:18:32 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	op_exe_else(char **op, t_cmd_arg *arg, \
							t_global *global, pid_t **pid)
{
	execve(op[0], op, global->env_ment);
	ft_putstr_fd("execve error\n", 2);
	all_free(&op, arg, global, pid);
	exit(127);
}

void	op_exe(char **op, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	if (arg->fd.cmd_num != 0 && arg->fd.fd1 == 0)
		dup2(arg->fd.pipe[arg->fd.cmd_num - 1][0], STDIN_FILENO);
	else if (arg->fd.cmd_num == 0 && arg->fd.fd1 == 0)
		dup2(arg->fd.temp_in, STDIN_FILENO);
	else
		dup2(arg->fd.fd1, STDIN_FILENO);
	if (arg->fd.cmd_num != arg->argc - 1 && arg->fd.fd2 == 0)
		dup2(arg->fd.pipe[arg->fd.cmd_num][1], STDOUT_FILENO);
	else if (arg->fd.cmd_num == arg->argc - 1 && arg->fd.fd2 == 0)
		dup2(arg->fd.temp_out, STDOUT_FILENO);
	else
		dup2(arg->fd.fd2, STDOUT_FILENO);


		
	if (arg->fd.fd1 != -1)
	{
		while (arg->fd.cmd_num > -1)
		{
			close(arg->fd.pipe[arg->fd.cmd_num][0]);
			close(arg->fd.pipe[arg->fd.cmd_num--][1]);
		}
		if (arg->flag == 1)
			builts_run(op, arg, global, pid);
		else
			op_exe_else(op, arg, global, pid);
	}
}	
