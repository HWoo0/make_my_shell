/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:25 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/04 13:42:52 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static long long	exit_atoi(const char *str, int *over, int i, int j)
{
	long		neg;
	long long	res;

	neg = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] && (str[i] == '0' || ft_isspace(str[i])))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9')) || \
		((i == 19 && neg == -1) && (str[i] == '9')))
			*over = 1;
		i++;
		j++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*over = 1;
	return (neg * res);
}

static void	str_exit(char **str, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	int	i;

	i = 0;
	if (str[1][i] == '-' || str[1][i] == '+')
		i++;
	while (str[1][i])
	{
		if (str[1][i] != '\t' && str[1][i] != '\v' && str[1][i] != '\f' && \
		str[1][i] != '\r')
		{
			if (str[1][i] < 48 || str[1][i] > 57)
			{
				ft_putstr_fd("exit\nminishell: exit: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				global->exit_stat = 2;
				all_free(&str, arg, global, pid);
				exit(global->exit_stat);
			}
		}
		i++;
	}
}

static void	over_case(char **str, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	long long	stat;
	int			over;

	over = 0;
	stat = exit_atoi(str[1], &over, 0, 0);
	if (over == 1)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		global->exit_stat = 2;
		all_free(&str, arg, global, pid);
		exit(global->exit_stat);
	}
	global->exit_stat = stat % 256;
}

static void	free_and_exit(char **str, t_cmd_arg *arg, \
							t_global *global, pid_t **pid)
{
	if (*pid[arg->fd.cmd_num] != 0)
		printf("exit\n");
	all_free(&str, arg, global, pid);
	exit(global->exit_stat);
}

void	exit_built(char **str, t_cmd_arg *arg, t_global *global, pid_t **pid)
{
	int	i;

	i = 1;
	global->exit_stat = 0;
	if (!str[1])
		free_and_exit(str, arg, global, pid);
	str_exit(str, arg, global, pid);
	while (str[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		global->exit_stat = 1;
		return ;
	}
	else
		over_case(str, arg, global, pid);
	free_and_exit(str, arg, global, pid);
}
