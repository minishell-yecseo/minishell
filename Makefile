# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:34:45 by yecnam            #+#    #+#              #
#    Updated: 2023/04/18 16:35:15 by yecnam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
BONUS_NAME		= minishell_bonus

SRC_DIR			= sources/
BONUS_SRC_DIR	= bonus/

SRC				= main.c unset.c cd_pwd.c export2.c\
				tree.c exe.c fork.c helpful_func.c simple_cmd.c \
				exefile.c built_in.c echo.c export.c \
				utils.c utils_list.c utils_replace_envp.c \
				utils_tree_build.c utils_syntax.c\
				exit.c one_built_in.c env.c unset_oldpath.c path_exe.c\
				utils_lexer.c here_doc_replace_envp.c \
				settings.c no_cmd.c utils_error.c update_lv.c\
				here_doc.c utils_asterisk.c signal.c program_end.c \
				func_err.c with_err_func.c tree_2.c tree_setting.c traverse.c\
				utils_lexer_2.c utils_lexer_3.c utils_lexer_4.c utils_list_2.c \
				utils_replace_envp_2.c utils_tree_build_2.c utils_syntax_2.c

BONUS_SRC		= main_bonus.c unset_bonus.c cd_pwd_bonus.c export2_bonus.c\
				tree_bonus.c exe_bonus.c fork_bonus.c helpful_func_bonus.c simple_cmd_bonus.c \
				exefile_bonus.c built_in_bonus.c echo_bonus.c export_bonus.c \
				utils_bonus.c utils_list_bonus.c utils_replace_envp_bonus.c \
				utils_tree_build_bonus.c utils_syntax_bonus.c\
				exit_bonus.c one_built_in_bonus.c env_bonus.c unset_oldpath_bonus.c path_exe_bonus.c\
				utils_lexer_bonus.c here_doc_replace_envp_bonus.c \
				settings_bonus.c no_cmd_bonus.c utils_error_bonus.c \
				here_doc_bonus.c utils_asterisk_bonus.c signal_bonus.c program_end_bonus.c \
				func_err_bonus.c with_err_func_bonus.c tree_2_bonus.c tree_setting_bonus.c traverse_bonus.c\
				utils_lexer_2_bonus.c utils_lexer_3_bonus.c utils_lexer_4_bonus.c utils_list_2_bonus.c \
				utils_replace_envp_2_bonus.c utils_tree_build_2_bonus.c utils_syntax_2_bonus.c

OBJS			= $(SRCS:.c=.o)
SRCS			= $(addprefix $(SRC_DIR), $(SRC))

BONUS_OBJS		= $(BONUS_SRCS:.c=.o)
BONUS_SRCS		= $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC))


INC			= -I./headers -I./libft -I${HOME}/.brew/opt/readline/include

LIB_DIR			= ./libft
LIB			= ./libft/libft.a

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
READLINE		= -lreadline -L${HOME}/.brew/opt/readline/lib

all : $(NAME)

%.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIB)
	$(CC) $(INC) $(CFLAGS) $(LIB) $(READLINE) -o $@ $^

$(LIB) :
	$(MAKE) -C $(LIB_DIR)

clean :
	rm -rf $(OBJS) $(BONUS_OBJS)
	$(MAKE) fclean -C $(LIB_DIR)

fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)

bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS) $(LIB)
	$(CC) $(INC) $(CFLAGS) $(LIB) $(READLINE) -o $@ $^

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
