/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_isop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:37 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 16:57:48 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	set_sp(char c, int *i, int *cnt)
{
	char	sp;

	if (c == '\"' && *cnt % 2 == 0)
	{
		(*i)++;
		(*cnt)++;
		sp = '\"';
	}
	else if (c == '\'' && *cnt % 2 == 0)
	{
		(*i)++;
		(*cnt)++;
		sp = '\'';
	}
	else if (c == '{' && *cnt % 2 == 0)
	{
		(*i)++;
		(*cnt)++;
		sp = '}';
	}
	else
		sp = ' ';
	return (sp);
}

void	is_left(char *str, t_split_arg *arg)
{
	arg->res = ft_realloc(arg->res, sizeof(char *) * (arg->k + 1), \
							sizeof(char *) * (arg->k + 2));
	if (str[arg->i + 1] == '<')
	{
		arg->res[arg->k] = ft_strdup("<<");
		(arg->j) += 2;
		(arg->i) += 2;
	}
	else
	{
		arg->res[arg->k] = ft_strdup("<");
		(arg->j)++;
		(arg->i)++;
	}
	(arg->k)++;
	while (((str[arg->i] == ' ' && str[arg->i] != '\0')) && \
			(str[arg->i] != '<' && str[arg->i] != '>' && str[arg->i] != '|'))
	{
		(arg->j)++;
		(arg->i)++;
	}
}

void	is_right(char *str, t_split_arg *arg)
{
	arg->res = ft_realloc(arg->res, sizeof(char *) * (arg->k + 1), \
							sizeof(char *) * (arg->k + 2));
	if (str[arg->i + 1] == '>')
	{
		arg->res[arg->k] = ft_strdup(">>");
		(arg->j) += 2;
		(arg->i) += 2;
	}
	else
	{
		arg->res[arg->k] = ft_strdup(">");
		(arg->j)++;
		(arg->i)++;
	}
	(arg->k)++;
	while (((str[arg->i] == ' ' && str[arg->i] != '\0')) && \
			(str[arg->i] != '<' && str[arg->i] != '>' && str[arg->i] != '|'))
	{
		(arg->j)++;
		(arg->i)++;
	}
}

void	is_pipe(char *str, t_split_arg *arg)
{
	arg->res = ft_realloc(arg->res, sizeof(char *) * (arg->k + 1), \
							sizeof(char *) * (arg->k + 2));
	arg->res[arg->k] = ft_strdup("|");
	(arg->i)++;
	(arg->j)++;
	(arg->k)++;
	while (((str[arg->i] == ' ' && str[arg->i] != '\0')) && \
			(str[arg->i] != '<' && str[arg->i] != '>' && str[arg->i] != '|'))
	{
		(arg->i)++;
		(arg->j)++;
	}
}
