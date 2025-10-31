/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_check_redirec.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:14:16 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/02 16:27:54 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	redirection_check2(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (((str[j] == '<' && (str[j + 1] && str[j + 1] == '<')) || \
			(str[j] == '>' && (str[j + 1] && str[j + 1] == '>'))) && \
			str[j + 2] && str[j + 2] == '\0')
			return (1);
		j++;
	}
	return (0);
}

int	redirection_check(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' && ((str[i + 1] && \
			(ft_strncmp(str[i + 1], "<", 1) == 0 || \
			ft_strncmp(str[i + 1], ">", 1) == 0)) || str[i + 1] == NULL))
			return (1);
		if (str[i][0] == '>' && ((str[i + 1] && \
			(ft_strncmp(str[i + 1], "<", 1) == 0 || \
			ft_strncmp(str[i + 1], ">", 1) == 0)) || str[i + 1] == NULL))
			return (1);
		if (redirection_check2(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
