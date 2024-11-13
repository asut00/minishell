/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:46:36 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/15 11:08:56 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_env_var
{
	char				*var_name;
	char				*value;
	int					is_printed;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_line_memory
{
	char					*line;
	struct s_line_memory	*next;
}	t_line_memory;

typedef struct s_commands
{
	char				*word;
	char				*f_word;
	int					type;
	struct s_commands	*next;
}	t_commands;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_var
{
	int					**exec_fds;
	int					**pipe_fds;
	char				***cmds;
	char				***infiles;
	char				***outfiles;
	char				**heredocs;
	int					**out_types;
	char				**cmd_paths;
	int					*redir;
	char				*env_path;
	char				**splitted_env;
	int					num_of_cmd;
	int					num_of_env_path;
	int					status;
	int					last_cmd_exit_status;
	int					*cmd_lengths;
	char				**tmp_envp;
	int					mode;
	int					saved_stdin;
	int					saved_stdout;
	int					do_the_exec;
	pid_t				*pids;
	t_commands			*commands;
	t_env_var			*env_var;
	t_garbage			*garbage_collector;
	t_line_memory		*line_memory;
	t_line_memory		*first_line;
	char				*input;
	struct sigaction	sa;

}				t_var;

typedef struct s_iter
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_iter;

typedef enum e_type
{
	NOT_DEFINED = -1,
	COMMAND,
	ARGS,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	PIPELINE,
	HEREDOC,
	LIM,
	OPTION,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_APPEND,
}	t_type;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

typedef unsigned long long	t_ull;

# define KEEP_GOING 0
# define STOP_INT 1
# define STOP_QUIT 2
# define STOP_EMPTY 3
# define STOP_INT_MAIN 4

# define IS_NOT_QUOTING 0
# define IS_SINGLE_QUOTING 1
# define IS_DOUBLE_QUOTING 2

# define NO_QUOTE 0
# define QUOTE 1

# define FAILURE 0
# define SUCCESS 1

# define CREATE 0
# define APPEND 1

# define MAIN 404
# define FALSE 0
# define TRUE 1

# define PATH_MAX 4096

# define WRONG_FORMAT 0
# define DEFINE 1
# define ADD 2

//libft_spe
void		ft_putchar_fd(char c, int fd);
char		*ft_strcat(char *dest, char *src);
char		**ft_split(char *s, char *charset, t_var *pvar);
void		ft_putnbr_fd(int n, int fd);
void		*ft_calloc(size_t nb_elem, size_t size_elem, t_var *var);
char		*ft_strchr(const char *str, int val);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_strjoin(char *s1, char *s2, t_var *var);
char		*ft_strjoin_no_free(char *s1, char *s2, t_var *var);
char		*ft_strjoin_malloc(char *s1, char *s2);
int			ft_strlcat(char *dest, const char *src, size_t n);
int			ft_strlcpy(char *dest, const char *src, size_t n);
char		*ft_substr(char *str, unsigned int start, size_t len, t_var *var);
char		*ft_substr_malloc(char *str, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n, t_var *var);
t_env_var	*ft_lstnew_env_var(char *var_name, char *value);
void		ft_lstadd_front_env_var(t_env_var **lst, t_env_var *new);
char		*ft_strdup_spe(const char *s1, t_var *pvar);
int			ft_strisnumber_spe(char *s);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_islonglong(const char *str);
long long	ft_atoll(const char *str);
t_ull		ft_atoull(const char *str);
int			ft_is_whitespace(char c);

//command_list_maipulator
t_commands	*ft_cmdlast(t_commands *lst);
t_commands	*ft_cmdnew(char *word, t_var *var);
void		ft_cmdadd_back(t_commands **lst, t_commands *new);
void		ft_cmdadd_next(t_commands *current, t_commands *new);
void		ft_cmdlst_free(t_var *var);

void		expand(t_var *var);
void		write_dollar(t_commands **c, char **f_word, t_var *var, char *v);
void		pre_expand(t_var *var);
void		lexing(t_var *var);
void		parsing(t_var *var);
int			check_command_error(t_var *var);
void		check_heredoc(t_var *var);
void		check_quotes(t_var *var);

//sig
void		set_signal_child_process(void);
void		signal_handler_special(int sig);
void		signal_handler_parent(int sig);
void		signal_handler_parent_after_readline(int sig);
void		set_signal_handler(int signum, void (*handler)(int));

//utils (check_command_error)
int			skip_quotes(char *input, int *type);
int			is_parse_error(int type, int type_prev);
void		parsing_error(int type);

//var_management
void		ft_env(t_var *var, char **cmds);
void		ft_env_export(t_var *var);
void		ft_unset(t_var *var, char **cmds);
int			is_export_format(char *s);
void		ft_export(t_var *var, char **cmds);
void		ft_export_one(t_var *var, char *new_var, int mode);
int			ft_export_spe(t_var *var, char **cmds);
void		var_init(t_var *var, char **env);
char		*ft_getenv(t_var *var, char *to_get);
void		ft_change_env_var(t_var *pvar, char *var_name, char *value);

//clear_all_and_exit.c
void		clear_all_and_exit(t_var *var, int exitvalue);

//garbage_management.c
t_garbage	*ft_garbagenew(void *content);
void		ft_cleargarbage(t_var *var);
void		ft_clear_line_memory(t_var *var);

//memory_management.c
void		*ft_malloc(int len, int size, t_var *pvar);
void		ft_free(t_var *var, void *content_to_find);
void		ft_malloc_env_var(t_var *pvar, char *var_name, char *value);

//split_line_memory.c
void		split_line(char *input, t_var *pvar);

//readline_memory.c
char		*ft_readline(char *prompt, t_var *pvar, int mode);

//exec.c
void		exec(t_var *var);
void		create_env_for_exec(t_var *var);
void		signal_handler_parent(int sig);

//init_cmd_array_loops.c
void		init_cmd_arrays(t_var *pvar, t_commands *commandline, t_iter *iter);

//pipex_init.c
void		pipex_init(t_var *pvar);
//builtins
void		ft_echo(t_var *pvar, int i);
void		ft_cd(t_var *pvar, int i);
char		*ft_get_cwd(t_var *pvar);
void		ft_pwd(t_var *pvar);
void		ft_exit(t_var *pvar, int i);

//exec_builtin.c
void		execbuiltin(t_var *pvar, int i);
///////////////////// PIPEX /////////////////////
//pipex_exec.c
void		pipex_execute_cmds(t_var *pvar);

//pipex_inits_and_wait.c
void		init_exec_vars(t_var *pvar);
void		init_pids(t_var *pvar);
void		wait_and_get_status(t_var *pvar);

//pipex_open_and_dup_fds.c
int			open_input_fd(t_var *pvar, int i, char *file);
int			open_output_fd(t_var *pvar, int i, char *file, int mode);

//pipex_exec_get_filefds.c
void		get_filefds_and_cmdpath(t_var *pvar, int i);

//handle_path.c
void		handle_absolute_path(t_var *pvar, int *path_found, int i);
void		handle_path_not_found(t_var *pvar, int i);
//pipex_get_cmdpaths.c
void		handle_absolute_path(t_var *pvar, int *path_found, int i);
void		handle_path_not_found(t_var *pvar, int i);
void		try_env_path_loop(t_var *pvar, int *path_found, int i, int *j);
int			cmd_is_builtin(t_var *pvar, int i);
void		pipex_get_cmd_path(t_var *pvar, int i);

int			check_if_path_or_builtin(t_var *pvar, int i);

//pipex_exec_handle_errors.c
void		handle_cmd_path_error(t_var *pvar, int i);
void		handle_execve_error(t_var *pvar);

//pipex_close.c
void		close_previous_pipes(t_var *pvar, int i);
void		close_all_pipes_children(t_var *pvar, int i);
void		close_all_pipes_parent(t_var *pvar);

/////////////////// SIGNAL ///////////////////
//signal_handlers.c
void		set_signal_handler(int signum, void (*handler)(int));
void		set_signal_child_process(void);
void		signal_handler_special(int sig);
void		signal_handler_parent(int sig);
void		signal_handler_parent_after_readline(int sig);

#endif
