/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirection_heredoc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:43:55 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 10:17:17 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	file_readline(char **line, int tmp_fd)
{
	char	*str;

	str = NULL;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if ((*line)[0] == '\'' || (*line)[0] == '\"')
		{
			if (ft_strncmp(str, (*line) + 1, \
				ft_strlen((*line)) - 2) == 0)
				break ;
		}
		if (ft_strcmp(str, (*line)) == 0)
			break ;
		write(tmp_fd, str, ft_strlen(str));
		write(tmp_fd, "\n", 1);
		free(str);
	}
	free(str);
	close(tmp_fd);
	exit (0);
}

static void	*heredoc_fork(char **line, char *name, int fd, t_global *global)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
		file_readline(line, fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &stat, 0);
		if (WIFSIGNALED(stat))
		{
			global->exit_stat = 130;
			printf("> \n");
			return (NULL);
		}
		free(*line);
		*line = name;
	}
	return (line);
}

static void	*is_heredoc(char **line, int num, t_global *global)
{
	int		tmp_fd;
	char	*tmp_name;
	char	*num_str;

	num_str = ft_itoa(num);
	tmp_name = ft_strjoin("/tmp/", num_str);
	free(num_str);
	if (!tmp_name)
	{
		printf("alloc error\n");
		return (NULL);
	}
	tmp_fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		free(tmp_name);
		printf("open error\n");
		return (NULL);
	}
	if (!heredoc_fork(line, tmp_name, tmp_fd, global))
		return (NULL);
	return (line);
}

void	*ft_creat_file(char ***line, t_global *global)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while ((*line)[i] != NULL)
	{
		if ((*line)[i][0] == '<' && (*line)[i][1] == '<')
		{
			i++;
			if (!is_heredoc(&(*line)[i], num++, global))
				return (NULL);
		}
		i++;
	}
	signal(SIGINT, sigfunc);
	return (line);
}
