/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:37 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 11:47:01 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_arg(t_split_arg *arg)
{
	arg->i = 0;
	arg->j = 0;
	arg->k = 0;
	arg->res = ft_calloc(1, sizeof(char *));
}

char	**mini_split(char *str, t_global *global)
{
	int			cnt;
	char		sp;

	init_arg(&(global->arg));
	cnt = 0;
	while (str[global->arg.i])
	{
		sp = set_sp(str[global->arg.i], &(global->arg.i), &cnt);
		if (str[global->arg.i] == '<' && \
					(sp != '\'' && sp != '\"' && sp != '}'))
			is_left(str, &(global->arg));
		else if (str[global->arg.i] == '>' && \
					(sp != '\'' && sp != '\"' && sp != '}'))
			is_right(str, &(global->arg));
		else if (str[global->arg.i] == '|' && \
					(sp != '\'' && sp != '\"' && sp != '}'))
			is_pipe(str, &(global->arg));
		else
		{
			if (not_op(str, sp, &cnt, &(global->arg)) == NULL)
				continue ;
		}
	}
	global->arg.res[global->arg.k] = NULL;
	return (global->arg.res);
}
