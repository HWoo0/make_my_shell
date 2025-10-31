/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:03:22 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/03 18:05:59 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	name_check(char *str)
{
	size_t	i;
	char	alpha_check;

	i = 0;
	alpha_check = 0;
	if (!str || !str[0] || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]))
			alpha_check = 1;
		else
		{
			if (ft_isdigit(str[i]) && !alpha_check)
				return (0);
			else if (str[i] == '+' && str[i + 1] == '=')
				break ;
			else if (!ft_isdigit(str[i] && str[i] != '-'))
				return (0);
		}
		i++;
	}
	return (1);
}

static char	**new_env(t_global *global)
{
	char	**new;
	size_t	cnt;
	size_t	i;

	i = 0;
	cnt = env_count(global->env_ment);
	new = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!new)
		return (NULL);
	while (i < cnt)
	{
		new[i] = ft_strdup(global->env_ment[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	print_export(char **str)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (str[i])
	{
		equ = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (str[i][j])
		{
			ft_putchar_fd(str[i][j], 1);
			if (str[i][j] == '=' && equ)
			{
				ft_putchar_fd('"', 1);
				equ--;
			}
			j++;
		}
		if (!equ)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_export(t_global *global)
{
	char	**new;
	char	*tmp;
	size_t	i;
	size_t	j;

	new = new_env(global);
	i = 0;
	while (new[i])
	{
		j = i + 1;
		while (new[j])
		{
			if (ft_strcmp(new[i], new[j]) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(new);
	ft_free_array(new);
}
