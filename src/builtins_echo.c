/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:07 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/03 15:10:20 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_built(char **str, t_global *global)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	global->exit_stat = 0;
	if (!(str[0]))
	{
		ft_putchar('\n');
		return (0);
	}
	else if (str[0][0] == '-' && str[0][1] == 'n' && str[0][2] == '\0')
		flag = 1;
	if (flag)
		i++;
	while (str[i])
	{
		ft_putstr(str[i]);
		if (!(str[i + 1]) && flag == 0)
			ft_putchar('\n');
		if (ft_strcmp(str[i], "") && str[i + 1])
			ft_putchar(' ');
		i++;
	}
	return (0);
}
