/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_notop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:37 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 17:55:07 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	next_sp(char *str, char sp, int *cnt, t_split_arg *arg)
{
	while (str[arg->i] && ((str[arg->i] != sp || \
			(str[arg->i + 1] && str[arg->i + 1] != '\0'))))
	{
		if (str[arg->i] == sp)
			(*cnt)++;
		arg->i++;
		if (str[arg->i] != sp && str[arg->i] && \
				str[arg->i + 1] && str[arg->i + 1] != ' ' && *cnt % 2 == 1)
			arg->i++;
		if ((str[arg->i] == ' ' || str[arg->i] == '<' || str[arg->i] == '>' \
				|| str[arg->i] == '|') && *cnt % 2 == 0)
			break ;
	}
	if (str[arg->i] == sp)
		arg->i++;
}

static void	sp_split(char *str, char *sp, int *cnt, t_split_arg *arg)
{
	while (str[arg->i] == ' ' && str[arg->i + 1] && str[arg->i + 1] != ' ')
	{
		arg->i++;
		arg->j++;
	}
	while (((str[arg->i] != *sp && str[arg->i] != '\0')) && \
			(str[arg->i] != '<' && str[arg->i] != '>' && str[arg->i] != '|'))
	{
		arg->i++;
		if ((str[arg->i] == '\"' || str[arg->i] == '\'' || \
				str[arg->i] == '}') && *cnt != 2)
		{
			if (str[arg->i] == str[arg->i + 1])
				arg->i += 2;
			else
			{
				(*cnt)++;
				*sp = str[arg->i++];
			}
		}
		if (*cnt == 2 && *sp != ' ')
			*sp = ' ';
	}
}

static void	creat_res(char *str, t_split_arg *arg)
{
	arg->res = ft_realloc(arg->res, sizeof(char *) * (arg->k + 1), \
							sizeof(char *) * (arg->k + 2));
	if (arg->j == 0)
		arg->res[arg->k] = ft_strldup(str + arg->j, arg->i);
	else if (str[arg->i] == '\'' || str[arg->i] == '\"')
		arg->res[arg->k] = ft_strldup(str + arg->j, arg->i - arg->j + 1);
	else
		arg->res[arg->k] = ft_strldup(str + arg->j, arg->i - arg->j);
	(arg->k)++;
	arg->j = arg->i;
}

static void	cnt_reset(char *str, char *sp, int *cnt, t_split_arg *arg)
{
	if (*cnt != 0)
	{
		*cnt = 0;
		*sp = ' ';
		if (str[arg->i] != '\0' && (str[arg->i] != '<' && \
				str[arg->i] != '>' && str[arg->i] != '|'))
		{
			arg->i++;
			arg->j++;
		}
	}
}

void	*not_op(char *str, char sp, int *cnt, t_split_arg *arg)
{
	if (*cnt == 1 && (sp == '\'' || sp == '\"' || sp == '}'))
		next_sp(str, sp, cnt, arg);
	else
		sp_split(str, &sp, cnt, arg);
	if (str[arg->i] && (str[arg->i + 1] && \
			str[arg->i + 1] == ' ') && *cnt % 2 != 0)
	{
		while (str[arg->i] == ' ')
		{
			arg->i++;
			arg->j++;
		}
		return (NULL);
	}
	creat_res(str, arg);
	cnt_reset(str, &sp, cnt, arg);
	while (((str[arg->i] == ' ' && str[arg->i] != '\0')) && \
			(str[arg->i] != '<' && str[arg->i] != '>' && str[arg->i] != '|'))
	{
		arg->i++;
		arg->j++;
	}
	return (str);
}
