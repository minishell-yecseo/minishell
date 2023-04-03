NAME = minishell

SRCS = main.c export.c unset.c cd_pwd.c\
		tree.c exe.c fork.c helpful_func.c simple_cmd.c \
		exefile.c helpful_func2.c built_in.c echo.c export.c \
		helpful_func3.c \
		utils.c ft_strings.c

OBJS = $(SRCS:.c=.o)
INC = ./

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
READLINE = -lreadline -L/Users/yecnam/.brew/opt/readline/lib 
OBJS_READLINE = -I/Users/yecnam/.brew/opt/readline/include

#READLINE = -lreadline -L/opt/homebrew/opt/readline/lib
#OBJS_READLINE = -I/opt/homebrew/opt/readline/include


all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(OBJS_READLINE) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(READLINE) -o $@ $^

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
