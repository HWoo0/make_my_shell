/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:06 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/03 18:13:07 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	update_value(char *str, size_t equal_index, size_t index, \
t_global *global)
{
	char	*env_name;
	char	*end;
	ssize_t	equ_env;

	if (equal_index == ft_strlen(str))
		return (0);
	equ_env = char_by_index(global->env_ment[index], '=');
	if (equ_env == -1)
	{
		equ_env = ft_strlen(global->env_ment[index]);
		env_name = global->env_ment[index];
		global->env_ment[index] = ft_strjoin(global->env_ment[index], "=");
		free(env_name);
	}
	env_name = ft_substr(global->env_ment[index], 0, (size_t)equ_env);
	if (!env_name)
		return (0);
	end = ft_substr(str, (equal_index + 1), ft_strlen(str));
	return (export_free(env_name, end, global));
}

static void	append_value(char *str, size_t plus_equ_idx, size_t index, \
t_global *global)
{
	char	*existing_value;
	char	*new;
	char	*result;
	char	*temp;
	char	*temp2;

	existing_value = ft_substr(global->env_ment[index], \
							char_by_index(global->env_ment[index], '=') + 1, \
									ft_strlen(global->env_ment[index]));
	new = ft_substr(str, plus_equ_idx + 2, ft_strlen(str));
	result = ft_strjoin(existing_value, new);
	free(existing_value);
	free(new);
	free(global->env_ment[index]);
	temp2 = ft_substr(str, 0, plus_equ_idx);
	temp = ft_strjoin(temp2, "=");
	global->env_ment[index] = ft_strjoin(temp, result);
	free(temp);
	free(temp2);
	free(result);
}

static void	add_new_env(char **str, char *env_name, size_t i, t_global *global)
{
	char	*end;
	size_t	count;
	size_t	plus_idx;

	count = (env_count(global->env_ment) + 1);
	global->env_ment = realloc_envs(count, global);
	plus_idx = char_by_index(str[i], '+');
	if (plus_idx != (size_t)-1 && char_by_index(str[i], '=') == plus_idx + 1)
	{
		env_name = ft_substr(str[i], 0, plus_idx);
		end = ft_substr(str[i], plus_idx + 1, ft_strlen(str[i]));
	}
	else
	{
		env_name = ft_substr(str[i], 0, char_by_index(str[i], '=') + 1);
		end = ft_substr(str[i], char_by_index(str[i], '=') + 1, \
		ft_strlen(str[i]));
	}
	if (!env_name || !end)
	{
		new_env_free(env_name, end);
		return ;
	}
	global->env_ment[count - 1] = ft_strjoin(env_name, end);
	new_env_free(env_name, end);
}

static void	update_export2(char **str, size_t plus_idx, size_t i, \
t_global *global)
{
	ssize_t	idx;
	char	*env_name;

	env_name = ft_substr(str[i], 0, plus_idx);
	idx = find_env(env_name, global);
	free(env_name);
	if (idx != -1)
		append_value(str[i], plus_idx, idx, global);
	else
		add_new_env(str, env_name, i, global);
}

void	update_export(char **str, size_t i, t_global *global)
{
	ssize_t	idx;
	size_t	plus_idx;
	size_t	equal_idx;
	char	*env_name;

	plus_idx = char_by_index(str[i], '+');
	equal_idx = char_by_index(str[i], '=');
	if (plus_idx != (size_t)-1 && equal_idx == plus_idx + 1)
	{
		update_export2(str, plus_idx, i, global);
		return ;
	}
	if (equal_idx == (size_t)-1)
		equal_idx = ft_strlen(str[i]);
	env_name = ft_substr(str[i], 0, equal_idx);
	idx = find_env(env_name, global);
	free(env_name);
	if (idx != -1)
		update_value(str[i], equal_idx, idx, global);
	else
		add_new_env(str, env_name, i, global);
}
