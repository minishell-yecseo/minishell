#ifndef TREE_H
# define TREE_H

# include "token.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <termios.h>

typedef struct s_node
{
	enum e_token	type;//can be PIPE, CMD, REDIR, SIMPLE_CMD
	struct s_cont	cont;
	//union u_cont	cont;//can be a pointer of struct s_pipe, s_cmd, s_redir, s_simple_cmd
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_tree
{
	struct s_node	*head;
	int				size;
	int				last;
	int				err;
	pid_t			pid;
	int				first;
	int				fds[2];
	int				stdfds[2];
	int				filefds[2];
	struct			termios term;
}					t_tree;

t_tree	*init_tree(void);
t_node	*create_node(t_token type);
void	insert_left(t_node *parent, t_node *child);
void	insert_right(t_node *parent, t_node *child);

int		traverse(t_tree *tree, t_node *cur, char ***envp);

void	print_token_type(t_node *node);
void	print_cont(t_cont *cont, t_token type);

void	exe_cur(t_tree *tree, t_node *cur, char ***envp);
void	wait_forks(t_tree *tree);

void	exe_simple_com(t_tree *tree, t_node *cur, char ***envp);
void	forked_exe(t_tree *tree, t_node *cur, char ***envp);
int		check_char(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		check_built_in(char *s, char **args, char ***envp);
int		check_path(char **envp);
int		check_is_path(char *s);
int		check_exefile(t_node *cur, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	last_simple_com(t_tree *tree, t_node *cur, char ***envp);
int		check_built_in(char *s, char **args, char ***envp);
int		echo(char **args);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_print_err(char *str);
char	**cp_envp(char **envp);
int		unset(char **arg, char ***envp);
char	**del_envp(char **envp, char *str);
void	free_envp(char ***envp);
char	*ft_strdup(const char *s1);

int		export(char **arg, char ***envp);
int		pwd(void);
int		cd(char **args, char ***envp);
int		ft_envpcmp(char *s1, char *s2);

char	*path_strjoin(char const *s1, char const *s2);
int 	ft_exit(char **args);
int		env(char **envp);
int		one_exe_built_in(char *s, char **args, char ***envp);
int		only_check_built_in(char *s);
char	**add_envp(char ***envp, char *str);

char	**oldpwd_envp(char ***envp, char *str);
int		f_envpcmp(char *s1, char *s2);
char	**make_big_arr(char ***envp);

#endif
