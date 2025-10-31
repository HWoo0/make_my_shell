/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_check_quote.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:13:47 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/11/30 15:13:50 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cnt_quote(char *str, char c, int *j, int *cnt)
{
	(*cnt)++;
	(*j)++;
	while (str[*j])
	{
		if (str[*j] == c && *cnt % 2 == 1)
		{
			(*cnt)++;
			(*j)++;
			break ;
		}
		(*j)++;
	}
}

int	quote_check(char **str)
{
	int		i;
	int		j;
	int		cnt;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			cnt = 0;
			if (str[i][j] == '\'' || str[i][j] == '\"')
				cnt_quote(str[i], str[i][j], &j, &cnt);
			else
				j++;
			if (cnt % 2 != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
