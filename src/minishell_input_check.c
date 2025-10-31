/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:12 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/03 17:42:44 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	pipe_check(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0 && i == 0)
			return (1);
		if (ft_strcmp(str[i], "|") == 0 && str[i + 1] == NULL)
			return (1);
		if (ft_strcmp(str[i], "|") == 0 && (str[i - 1] && \
			(ft_strcmp(str[i - 1], "|") == 0 || \
				ft_strncmp(str[i - 1], "<", 1) == 0 || \
				ft_strncmp(str[i - 1], ">", 1) == 0)))
		{
			if (str[i][0] != '\"' && str[i][0] != '\'')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**input_check(char ***str)
{
	if (quote_check(*str) || redirection_check(*str) || pipe_check(*str))
	{
		printf("input error\n");
		ft_free(*str);
		return (NULL);
	}
	return (*str);
}
