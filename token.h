#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token
{
	PIPE,
	CMD,
	REDIR,
	SIMPLE_CMD
}			t_token;

typedef enum e_redir_type
{
	IN,
	HERE_DOC,
	OUT_T,
	OUT_A
}			t_redir_type;

typedef struct s_cont
{
	int				is_pipe;
	int				fds[2];
	int				filefds[2];
	t_redir_type	redir_type;
	char			*file_name;
	int				fd;
	char			*path;
	char			**args;
}			t_cont;

/*
typedef struct s_pipe
{
	int		fds[2];
	int		is_pipe;
}			t_pipe;

typedef struct s_cmd
{
	int	none;
}			t_cmd;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file_name;
	int				fd;
}			t_redir;

typedef struct s_simple_cmd
{
	char	*path;
	char	**args;
}			t_simple_cmd;

typedef union u_cont
{
	t_pipe			pipe;
	t_cmd			cmd;
	t_redir			redir;
	t_simple_cmd	simple_cmd;
}			t_cont;
*/

#endif
