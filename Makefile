NAME			= minishell

SRC_DIR			= sources/

SRC				= main.c unset.c cd_pwd.c export2.c\
				tree.c exe.c fork.c helpful_func.c simple_cmd.c \
				exefile.c built_in.c echo.c export.c \
				utils.c utils_list.c utils_replace_envp.c \
				utils_tree_build.c utils_syntax.c\
				exit.c one_built_in.c env.c unset_oldpath.c path_exe.c\
				utils_lexer.c here_doc_replace_envp.c \
				settings.c no_cmd.c utils_error.c debug.c \
				here_doc.c utils_asterisk.c signal.c program_end.c \
				func_err.c


OBJS			= $(SRCS:.c=.o)

SRCS			= $(addprefix $(SRC_DIR), $(SRC))
#OBJS 			= $(SRCS:.c=.o)

INC			= -I./headers -I./libft -I${HOME}/.brew/opt/readline/include

LIB_DIR			= ./libft
LIB			= ./libft/libft.a

CC				= cc
CFLAGS			= #-g3 #-fsanitize=address #-Wall -Wextra -Werror
READLINE		= -lreadline -L${HOME}/.brew/opt/readline/lib

#READLINE		= -lreadline -L/opt/homebrew/opt/readline/lib
#OBJS_READLINE	= -I/opt/homebrew/opt/readline/include


all : $(NAME)

%.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIB)
	$(CC) $(INC) $(CFLAGS) $(LIB) $(READLINE) -o $@ $^

$(LIB) :
	$(MAKE) -C $(LIB_DIR)

clean :
	rm -rf $(OBJS)
	$(MAKE) fclean -C $(LIB_DIR)

fclean : clean
	rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
