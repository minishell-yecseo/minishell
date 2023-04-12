#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/signal.h>
# include <signal.h> 
# include "utils.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		g_last_exit_code;
void	exe_cur(t_tree *tree, t_node *cur, char ***envp);
void	wait_forks(t_tree *tree);

void	exe_simple_com(t_tree *tree, t_node *cur, char ***envp);
void	forked_exe(t_tree *tree, t_node *cur, char ***envp);
int		check_char(char *s, char c);
int		check_built_in(char *s, char **args, char ***envp);
int		check_path(char **envp);
int		check_is_path(char *s);
int		check_exefile(t_node *cur, char **envp);
void	last_simple_com(t_tree *tree, t_node *cur, char ***envp);
int		check_built_in(char *s, char **args, char ***envp);
int		echo(char **args);

char	**cp_envp(char **envp);
int		unset(char **arg, char ***envp);
char	**del_envp(char **envp, char *str);
void	free_envp(char ***envp);

int		export(char **arg, char ***envp);
int		pwd(void);
int		cd(char **args, char ***envp);
int		ft_envpcmp(char *s1, char *s2);

char	*path_strjoin(char const *s1, char const *s2);
int		ft_exit(char **args);
int		env(char **envp);
int		one_exe_built_in(char *s, char **args, char ***envp);
int		only_check_built_in(char *s);
char	**add_envp(char ***envp, char *str);

char	**oldpwd_envp(char ***envp, char *str);
int		f_envpcmp(char *s1, char *s2);
char	**make_big_arr(char ***envp);
void	path_exe(char **args, char ***envp);

void	print_init_msg(void);
char	*get_init_logo(void);
void	no_cmd(t_tree *tree, t_node *cur, char ***envp);
int		key_cmp(char *s1, char *s2);
char	**ordering_envp(char **envp);
void	export_print_envp(char **envp);
int		here_traverse(t_tree *tree, t_node *cur, char ***envp);
char	*ft_itos(int n);
void	here_del(void);
void	minishell_sig_setting(struct sigaction *sig, struct termios *old_term, struct termios *term);
void	restore_sig(void);
void	change_sig(t_tree *tree);
void	ignore_sig(void);
void	program_end(struct termios old_term);

#endif
