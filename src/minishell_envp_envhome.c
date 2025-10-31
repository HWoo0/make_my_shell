/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp_envhome.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:52:05 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 13:59:11 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*env_home_new(char **str, char *tmp, int i)
{
	int		str_len;
	int		tmp_len;
	int		new_i;
	char	*new;

	str_len = ft_strlen((*str));
	tmp_len = ft_strlen(tmp);
	new = malloc(str_len + tmp_len);
	if (!new)
		return (NULL);
	new_i = tmp_len;
	ft_strlcpy(new, tmp, tmp_len + 1);
	while ((*str)[i] != '\0')
		new[new_i++] = (*str)[i++];
	new[new_i] = '\0';
	return (new);
}

int	env_home( char **line, char **str, int *str_i, t_global *global)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 1;
	tmp = ft_getenv(global, "HOME");
	if (tmp == NULL)
		tmp = ft_calloc(1, 1);
	if ((*str)[i] == '\0')
	{
		free(*line);
		(*line) = tmp;
	}
	else if ((*str)[i] == '/')
	{
		new = env_home_new(str, tmp, i);
		if (!new)
			return (0);
		change_line(line, &new);
		*str_i += ft_strlen(tmp);
		free(tmp);
	}
	*str = *line;
	return (1);
}
