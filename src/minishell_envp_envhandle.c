/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp_envhandle.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:42:24 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 10:13:38 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_symbol(char c)
{
	if ((33 <= c && 47 >= c) || c == 58 || c == 59 || c == 61 || c == 64 || \
		(91 <= c && 94 >= c) || c == 96 || c == 123 || c == 125 || c == 126)
		return (1);
	return (0);
}

static void	find_end(char *str, int *end)
{
	while (str[*end])
	{
		if (str[*end] == '\0' || str[*end] == ' ' || \
			str[*end] == '$' || str[*end] == '\"' || is_symbol(str[*end]))
			break ;
		(*end)++;
	}
}

static char	*creat_env_str(char *str, int start, int end, t_global *global)
{
	char	*env_str;
	char	*env;
	int		envp_i;

	env = malloc(end - start);
	envp_i = 0;
	if (!env)
		return (NULL);
	while (envp_i < end - start - 1)
	{
		env[envp_i] = str[start + 1 + envp_i];
		envp_i++;
	}
	env[envp_i] = '\0';
	env_str = ft_getenv(global, env);
	free(env);
	return (env_str);
}

static char	*trance_env(char *str, int *start, int end, t_global *global)
{
	char	*env_str;
	char	*new;

	env_str = creat_env_str(str, (*start), end, global);
	if (env_str)
	{
		new = new_line(env_str, str, (*start), end);
		(*start) += (ft_strlen(env_str) - 1);
		free(env_str);
	}
	else
	{
		new = new_line(NULL, str, (*start), end);
		(*start)--;
	}
	return (new);
}

void	dollar_handle(char **line, char **str, int *start, t_global *global)
{
	int		end;
	char	*new;
	char	*num;

	end = (*start) + 1;
	if ((*str)[end] == '?')
	{
		num = ft_itoa(global->exit_stat);
		new = new_line(num, *str, (*start), ++end);
		(*start) += (ft_strlen(num) - 1);
		free(num);
	}
	else
	{
		find_end(*str, &end);
		if ((end - (*start) == 1 && (*str)[(*start) + 1] == '\0') || \
			((*str)[end - 1] && (*str)[end - 1] == '$'))
			return ;
		new = trance_env((*str), start, end, global);
	}
	change_line(line, &new);
	*str = *line;
}
