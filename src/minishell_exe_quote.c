/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:07:08 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 09:01:19 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	is_quote(char op, char temp)
{
	char	quote;

	quote = 0;
	if (op == '\"' && temp == '\"')
		quote = '\"';
	else if (op == '\'' && temp == '\'')
		quote = '\'';
	return (quote);
}

static void	new_str(char **op, char quote, int *i)
{
	char	*new;
	int		k;
	int		l;

	new = ft_calloc(sizeof(char), ft_strlen(*op));
	k = 0;
	l = 0;
	while (k < *i)
		new[l++] = (*op)[k++];
	k++;
	while (((*op)[k] != '\0' && (*op)[k] != quote))
		new[l++] = (*op)[k++];
	k++;
	*i = k - 2;
	while ((*op)[k] != '\0')
		new[l++] = (*op)[k++];
	free(*op);
	(*op) = ft_strdup(new);
	free(new);
}

void	remove_quote(char ***op, char **temp, t_global *global)
{
	int		j;
	int		i;
	int		t_i;
	char	quote;

	j = 0;
	while ((*op)[j] != NULL)
	{
		i = 0;
		t_i = 0;
		while (i < (int)ft_strlen((*op)[j]))
		{
			quote = is_quote((*op)[j][i], temp[j][t_i]);
			if (quote)
			{
				new_str(&(*op)[j], quote, &i);
				move_index(temp[j], quote, &t_i);
			}
			else
				not_quote(temp[j], &i, &t_i, global);
		}
		j++;
	}
}
