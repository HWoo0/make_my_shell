/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_quote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:14:21 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 10:12:54 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_start_end(char *str, int *t_i, int *start, int *end)
{
	while (str[*t_i] && str[*t_i] == '$')
		(*t_i)++;
	*start = *t_i;
	while (str[*t_i] && str[*t_i] != '\"' && str[*t_i] != '\'' \
		&& str[*t_i] != '$')
		(*t_i)++;
	*end = *t_i - 1;
}

static void	next_index(char *str, int *t_i, int *i, t_global *global)
{
	int		start;
	int		end;
	int		len;
	char	*res;
	char	*env;

	set_start_end(str, t_i, &start, &end);
	if (end >= start)
	{
		res = ft_substr(str, start, end - start + 1);
		env = ft_getenv(global, res);
		len = ft_strlen(env);
		if (len > 0)
			(*i) += len;
		else
			(*i) += end - start + 1;
		free(res);
		free(env);
	}
	else if ((*t_i) == 1)
		(*i)++;
	else
		(*i) += (*t_i) - 1;
}

void	not_quote(char *temp, int *i, int *t_i, t_global *global)
{
	if (temp[0] == '~')
	{
		(*t_i)++;
		(*i) += ft_strlen(ft_getenv(global, "HOME"));
	}
	else
		next_index(temp, t_i, i, global);
}
