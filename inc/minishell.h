/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:59:17 by hyeojeon          #+#    #+#             */
/*   Updated: 2024/12/04 13:00:16 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_split_arg
{
	int		i;
	int		j;
	int		k;
	char	**res;
}				t_split_arg;

typedef struct s_global
{
	char		**env_ment;
	int			exit_stat;
	int			err_flag;
	t_split_arg	arg;
}				t_global;

typedef struct s_fd
{
	int	**pipe;
	int	fd1;
	int	fd2;
	int	temp_in;
	int	temp_out;
	int	pipe_num;
	int	cmd_num;
}				t_fd;

typedef struct s_cmd_arg
{
	int		argc;
	int		flag;
	int		pipe_cnt;
	t_fd	fd;
}				t_cmd_arg;

/*minishell_envp.c*/
void		ft_ifenvp(char **line, t_global *global);
void		change_line(char **line, char **new);
char		*new_line(char *env, char *str, int start, int end);

/*minishell_envp_envhandle.c*/
void		dollar_handle(char **line, char **str, int *start, \
							t_global *global);

/*minishell_envp_envhome.c*/
int			env_home( char **line, char **str, int *str_i, t_global *global);

/*minishell_exe.c*/
void		exe_cmd(char **argv, t_fd fd, t_global *global);

/*minishell_exe_creatcmd.c*/
char		**creat_cmd(char **argv, int *index, t_fd *fd, t_global *global);

/*minishell_exe_fd.c*/
void		fd_init(t_fd *fd, int argc);
void		fd_close_free(t_fd *fd, int argc);
void		reset_io(t_fd *fd);

/*minishell_exe_opexe.c*/
void		op_exe(char **op, t_cmd_arg *arg, t_global *global, pid_t **pid);

/*minishell_exe_opinit.c*/
void		opinit(char ***arg, t_global *global, int *flag);

/*minishell_exe_quote.c*/
void		remove_quote(char ***op, char **temp, t_global *global);
void		not_quote(char *temp, int *i, int *t_i, t_global *global);

/*minishell_exe_runningcmd.c*/
void		running_cmd(char **argv, t_cmd_arg *arg, t_global *global);
void		all_free(char ***cmd, t_cmd_arg *arg, \
						t_global *global, pid_t **pid);

/*minishell_redirection.c*/
char		**ft_redirection_file(char **line, t_fd *fd, \
									t_global *global, int i);

/*minishell_redirection_heredoc.c*/
void		*ft_creat_file(char ***line, t_global *global);

/*minishell_split.c*/
char		**mini_split(char *str, t_global *global);

/*minishell_split_isop.c*/
char		set_sp(char c, int *i, int *cnt);
void		is_left(char *str, t_split_arg *arg);
void		is_right(char *str, t_split_arg *arg);
void		is_pipe(char *str, t_split_arg *arg);

/*minishell_split_notop.c*/
void		*not_op(char *str, char sp, int *cnt, t_split_arg *arg);

/*minishell_input_check.c*/
char		**input_check(char ***str);

/*minishell_input_check_quote*/
int			quote_check(char **str);

/*minishell_input_check_redirec.c*/
int			redirection_check(char **str);

/*minishell_signal.c*/
void		sigfunc(int signo);

/*minishell_utils1.c*/
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcat(char *dst, const char *src);
void		*ft_realloc(void *arr, int size, int new_size);
char		*ft_getenv(t_global *global, char *str);
char		*ft_join(char const *s1, char const *s2);
char		*ft_strldup(char *str, int len);
char		*ft_strstr(const char *big, const char *little, size_t len);
void		ft_free(char **str);
void		move_index(char *temp, char quote, int *i);

/*builtins_echo.c*/
int			echo_built(char **str, t_global *global);

/*builtins_env.c*/
int			env_built(char **str, char **envp, t_global *global);

/*builtins_pwd.c*/
int			pwd_built(void);

/*builtins_cd.c*/
int			cd_built(char **str, t_global *global);
int			set_dir(char *path, int home, t_global *global);
int			s_path(char **str, t_global *global);

/*builtins_export_utils1.c*/
int			name_check(char *str);
void		sort_export(t_global *global);

/*builtins_export_utils2.c*/
void		update_export(char **str, size_t i, t_global *global);

/*builtins_export.c*/
int			export_built(char **str, t_global *global);
void		new_env_free(char *env_name, char *end);

/*builtins_unset.c*/
int			unset_built(char **str, t_global *global);

/*builtins_exit.c*/
void		exit_built(char **str, t_cmd_arg *arg, \
							t_global *global, pid_t **pid);

/*builtins_check.c*/
int			builts_check(char **str);
void		builts_run(char **str, t_cmd_arg *arg, \
							t_global *global, pid_t **pid);

/*builtins_utils1.c*/
int			ft_isspace(int c);
void		ft_putchar(char c);
void		ft_putnstr(char *str, int n);
void		ft_putstr(char *s);
char		**ft_copy_envp(char **envp);

/*builtins_utils2.c*/
size_t		char_by_index(char *str, char c);
int			ft_strequ(const char *s1, const char *s2);
char		*get_env(char *env, t_global *global);
ssize_t		find_env(char *env, t_global *global);
size_t		env_count(char **env_ment);

/*builtins_utils3.c*/
int			set_env(char *env, char *new_env, t_global *global);
char		**realloc_envs(size_t size, t_global *global);
void		ft_free_array(char **array);
int			export_free(char *env_name, char *end, t_global *global);

#endif