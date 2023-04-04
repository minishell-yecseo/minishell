NAME			= minishell

SRC_DIR			= sources/

SRC			= main.c export.c unset.c cd_pwd.c\
				tree.c exe.c fork.c helpful_func.c simple_cmd.c \
				exefile.c helpful_func2.c built_in.c echo.c export.c \
				helpful_func3.c \
				utils.c ft_strings.c utils_list.c utils_tokenizer.c\
				utils_tree_build.c \
				exit.c one_built_in.c env.c

OBJS			= $(SRCS:.c=.o)

SRCS			= $(addprefix $(SRC_DIR), $(SRC))
#OBJS 			= $(SRCS:.c=.o)

INC				= ./headers

CC				= cc
CFLAGS			= -g #-Wall -Wextra -Werror
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
