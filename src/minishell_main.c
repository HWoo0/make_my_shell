/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:10 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 12:59:22 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	arg_init(t_fd *fd, t_global *global, char **envp)
{
	global->env_ment = ft_copy_envp(envp);
	global->exit_stat = 0;
	global->err_flag = 0;
	fd->temp_in = dup(STDIN_FILENO);
	fd->temp_out = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigfunc);
}

static int	main_while(t_fd *fd, t_global *global)
{
	char		*res;
	char		**line;
	char		name[1024];

	getcwd(name, 1024);
	ft_strcat(name, "$ ");
	res = readline(name);
	if (res == NULL)
		return (1);
	if (res[0] == '\0')
	{
		free(res);
		return (2);
	}
	add_history(res);
	line = mini_split(res, global);
	free(res);
	if (!line)
		return (1);
	if (!input_check(&line))
		return (2);
	exe_cmd(line, *fd, global);
	ft_free(line);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int			stat;
	int			exit_num;
	t_fd		fd;
	t_global	global;

	arg_init(&fd, &global, envp);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	while (ac > 0 || av)
	{
		stat = main_while(&fd, &global);
		if (stat == 1)
			break ;
		else if (stat == 2)
			continue ;
	}
	exit_num = global.exit_stat;
	ft_free(global.env_ment);
	printf("exit\n");
	return (exit_num);
}
