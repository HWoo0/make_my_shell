NAME			=	minishell
LIBFT			=	libft
INC				=	inc
INCLUDE			=	-Iinc
SRC_DIR			=	src/
OBJ_DIR			=	obj/
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
LFLAGS			=	-lreadline
RM				=	rm -f


MANDATORY_SRCS =									\
					minishell_split					\
					minishell_split_isop			\
					minishell_split_notop			\
					minishell_envp					\
					minishell_envp_envhandle		\
					minishell_envp_envhome			\
					minishell_main					\
					minishell_exe					\
					minishell_exe_creatcmd			\
					minishell_exe_fd				\
					minishell_exe_opexe				\
					minishell_exe_opinit			\
					minishell_exe_quote				\
					minishell_exe_quote2			\
					minishell_exe_runningcmd		\
					minishell_redirection			\
					minishell_redirection_heredoc	\
					minishell_input_check			\
					minishell_input_check_quote		\
					minishell_input_check_redirec	\
					minishell_signal				\
					minishell_utils1				\
					minishell_utils2				\
					builtins_check					\
					builtins_echo					\
					builtins_env					\
					builtins_pwd					\
					builtins_cd						\
					builtins_export					\
					builtins_export_utils1			\
					builtins_export_utils2			\
					builtins_unset					\
					builtins_exit					\
					builtins_utils1					\
					builtins_utils2					\
					builtins_utils3			

SRCS 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(MANDATORY_SRCS)))
OBJS 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(MANDATORY_SRCS)))

all:				$(NAME)

$(NAME) : 			$(OBJS) libft.a
					@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(INCLUDE) libft.a -o $(NAME)

libft.a:
					@make -C $(LIBFT)
					@cp $(LIBFT)/libft.a .
$(OBJ_DIR)%.o :		$(SRC_DIR)%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
					@make clean -C $(LIBFT)
					@$(RM) -r $(OBJ_DIR)
					@$(RM) libft.a
					
fclean:				clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)/libft.a


re:
					@make fclean
					@make all

.PHONY:				all clean fclean re
