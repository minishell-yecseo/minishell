NAME			= minishell

SRC_DIR			= sources/

SRC				= main.c unset.c cd_pwd.c \
				tree.c exe.c fork.c helpful_func.c simple_cmd.c \
				exefile.c built_in.c echo.c export.c \
				utils.c utils_list.c utils_replace_envp.c \
				utils_tree_build.c ft_strings_5.c utils_syntax.c\
				ft_strings.c ft_strings_2.c ft_strings_3.c ft_strings_4.c \
				exit.c one_built_in.c env.c unset_oldpath.c path_exe.c\
				utils_lexer.c err_exit.c here_doc_replace_envp.c

OBJS			= $(SRCS:.c=.o)

SRCS			= $(addprefix $(SRC_DIR), $(SRC))
#OBJS 			= $(SRCS:.c=.o)

INC				= ./headers

CC				= cc
CFLAGS			= -g -fsanitize=address #-Wall -Wextra -Werror
READLINE		= -lreadline -L${HOME}/.brew/opt/readline/lib
OBJS_READLINE	= -I${HOME}/.brew/opt/readline/include

#READLINE		= -lreadline -L/opt/homebrew/opt/readline/lib
#OBJS_READLINE	= -I/opt/homebrew/opt/readline/include


all : $(NAME)

%.o : %.c
	$(CC) -I $(INC) $(CFLAGS) $(OBJS_READLINE) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) -I $(INC) $(CFLAGS) $(READLINE) -o $@ $^

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
