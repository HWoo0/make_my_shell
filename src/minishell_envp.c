/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:16 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 13:59:19 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_line(char **line, char **new)
{
	free(*line);
	(*line) = ft_strdup(*new);
	if (!(*line))
		return ;
	free(*new);
}

char	*new_line(char *env, char *str, int start, int end)
{
	int		envp_len;
	int		str_len;
	int		new_i;
	int		i;
	char	*new;

	envp_len = ft_strlen(env);
	str_len = ft_strlen(str);
	new_i = 0;
	i = 0;
	new = malloc(envp_len + str_len - (end - start) + 1);
	if (!new)
		return (NULL);
	while (new_i < start)
	{
		new[new_i] = str[new_i];
		new_i++;
	}
	while (i < envp_len)
		new[new_i++] = env[i++];
	i = end;
	while (str[i] && i < str_len)
		new[new_i++] = str[i++];
	new[new_i] = '\0';
	return (new);
}

static void	env_handle(char **str, int *start, char **line, t_global *global)
{
	int		cnt;

	cnt = 0;
	while ((*str)[*start] != '\0')
	{
		if ((*str)[*start] == '\"')
			cnt++;
		if ((*str)[*start] == '\'' && cnt % 2 == 0)
		{
			move_index(*str, '\'', start);
			continue ;
		}
		if ((*str)[*start] == '$')
			dollar_handle(line, str, start, global);
		(*start)++;
	}
}

static void	env_heredoc(char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && \
		((*line)[i + 1] == '\'' || (*line)[i + 1] == '\"'))
		{
			temp = ft_strdup((*line));
			free((*line));
			(*line) = ft_strdup(temp + 1);
			free(temp);
			i--;
		}
		i++;
	}
}

void	ft_ifenvp(char **line, t_global *global)
{
	int		line_i;
	int		start;
	char	*str;

	line_i = 0;
	while (line[line_i])
	{
		start = 0;
		str = line[line_i];
		if (str[0] == '~')
		{
			if (env_home(&line[line_i], &str, &start, global) == 0)
				return ;
		}
		if (ft_strcmp(str, "<<") == 0)
			env_heredoc(&line[++line_i]);
		else
			env_handle(&str, &start, &line[line_i], global);
		line_i++;
	}
}
