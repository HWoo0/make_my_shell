
NAME			=		libft.a
INCLUDE			=		-Iinc/
SRC_DIR			=		src/
OBJ_DIR			=		obj/
CC				=		cc
CFLAGS			=		-Wall -Wextra -Werror
AR				=		ar rc
RM				=		rm -f

LIBFT_DIR		=		libft/
LIBFT			=		ft_isalpha					\
						ft_isdigit					\
						ft_isalnum					\
						ft_isascii					\
						ft_isprint					\
						ft_strlen					\
						ft_memset					\
						ft_bzero					\
						ft_memcpy					\
						ft_memmove					\
						ft_strlcpy					\
						ft_strlcat					\
						ft_toupper					\
						ft_tolower					\
						ft_strchr					\
						ft_strrchr					\
						ft_strncmp					\
						ft_memchr					\
						ft_memcmp					\
						ft_strnstr					\
						ft_atoi						\
						ft_calloc					\
						ft_strdup					\
						ft_substr					\
						ft_strjoin					\
						ft_strtrim					\
						ft_split					\
						ft_itoa						\
						ft_strmapi					\
						ft_striteri					\
						ft_putchar_fd				\
						ft_putstr_fd				\
						ft_putendl_fd				\
						ft_putnbr_fd				\
						ft_lstnew_bonus				\
						ft_lstadd_front_bonus		\
						ft_lstsize_bonus			\
						ft_lstlast_bonus			\
						ft_lstadd_back_bonus		\
						ft_lstdelone_bonus			\
						ft_lstclear_bonus			\
						ft_lstiter_bonus			\
						ft_lstmap_bonus

SRC_FILES		=		$(addprefix $(LIBFT_DIR), $(LIBFT))

SRC				=		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

start:
						@make all

all:					$(NAME)

$(NAME):				$(OBJ)
						@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
						@mkdir -p $(OBJ_DIR)$(LIBFT_DIR)
						@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
						
clean:
						@$(RM) -r $(OBJ_DIR)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

.PHONY:		all clean fclean re